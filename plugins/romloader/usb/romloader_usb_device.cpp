/***************************************************************************
 *   Copyright (C) 2007 by Christoph Thelen                                *
 *   doc_bacardi@users.sourceforge.net                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include "romloader_usb_device.h"

#include <errno.h>


const romloader_usb_device::NETX_USB_DEVICE_T romloader_usb_device::atNetxUsbDevices[2] =
{
	{
		"netX500",
		0x0cc4,
		0x0815,
		ROMLOADER_CHIPTYP_NETX500,
		ROMLOADER_ROMCODE_ABOOT,
		0x81,
		0x01
	},
	{
		"netX10",
		0x1939,
		0x000c,
		ROMLOADER_CHIPTYP_NETX10,
		ROMLOADER_ROMCODE_HBOOT,
		0x83,
		0x04
	}
};



romloader_usb_device::romloader_usb_device(const char *pcPluginId)
 : m_pcPluginId(NULL)
 , m_ptFirstCard(NULL)
 , m_ptLastCard(NULL)
{
	m_pcPluginId = strdup(pcPluginId);

	initCards();
}


romloader_usb_device::~romloader_usb_device(void)
{
	deleteCards();

	if( m_pcPluginId!=NULL )
	{
		free(m_pcPluginId);
	}
}


void romloader_usb_device::initCards(void)
{
	tBufferCard *ptCard;


	if( m_ptFirstCard!=NULL )
	{
		deleteCards();
	}

	ptCard = new tBufferCard;
	ptCard->pucEnd = ptCard->aucData + mc_sizCardSize;
	ptCard->pucRead = ptCard->aucData;
	ptCard->pucWrite = ptCard->aucData;
	ptCard->ptNext = NULL;

	m_ptFirstCard = ptCard;
	m_ptLastCard = ptCard;
}


void romloader_usb_device::deleteCards(void)
{
	tBufferCard *ptCard;
	tBufferCard *ptNextCard;


	ptCard = m_ptFirstCard;
	while( ptCard!=NULL )
	{
		ptNextCard = ptCard->ptNext;
		delete ptCard;
		ptCard = ptNextCard;
	}
	m_ptFirstCard = NULL;
	m_ptLastCard = NULL;
}


void romloader_usb_device::writeCards(const unsigned char *pucBuffer, size_t sizBufferSize)
{
	size_t sizLeft;
	size_t sizChunk;
	tBufferCard *ptCard;


	sizLeft = sizBufferSize;
	while( sizLeft>0 )
	{
		// get free space in the current card
		sizChunk = m_ptLastCard->pucEnd - m_ptLastCard->pucWrite;
		// no more space -> create a new card
		if( sizChunk==0 )
		{
			ptCard = new tBufferCard;
			ptCard->pucEnd = ptCard->aucData + mc_sizCardSize;
			ptCard->pucRead = ptCard->aucData;
			ptCard->pucWrite = ptCard->aucData;
			ptCard->ptNext = NULL;
			// append new card
			m_ptLastCard->ptNext = ptCard;
			// close old card
			m_ptLastCard->pucWrite = NULL;
			// set the new last pointer
			m_ptLastCard = ptCard;
			// the new card is empty
			sizChunk = mc_sizCardSize;
		}
		// limit chunk to request size
		if( sizChunk>sizLeft )
		{
			sizChunk = sizLeft;
		}
		// copy data
		memcpy(m_ptLastCard->pucWrite, pucBuffer, sizChunk);
		// advance pointer
		m_ptLastCard->pucWrite += sizChunk;
		pucBuffer += sizChunk;
		sizLeft -= sizChunk;
	}
}


size_t romloader_usb_device::readCards(unsigned char *pucBuffer, size_t sizBufferSize)
{
	size_t sizRead;
	size_t sizLeft;


	sizLeft = sizBufferSize;
	do
	{
		sizRead = readCardData(pucBuffer, sizLeft);
		pucBuffer += sizRead;
		sizLeft -= sizRead;
	} while( sizRead!=0 && sizLeft>0 );

	return sizBufferSize-sizLeft;
}


size_t romloader_usb_device::readCardData(unsigned char *pucBuffer, size_t sizBufferSize)
{
	size_t sizRead;
	tBufferCard *ptOldCard;
	tBufferCard *ptNewCard;


	if( m_ptFirstCard==NULL )
	{
		sizRead = 0;
	}
	else if( m_ptFirstCard->pucWrite!=NULL )
	{
		// get the number of bytes left in this card
		sizRead = m_ptFirstCard->pucWrite - m_ptFirstCard->pucRead;
		if( sizRead>sizBufferSize )
		{
			sizRead = sizBufferSize;
		}
		// card can be empty
		if( sizRead>0 )
		{
			// copy the data
			memcpy(pucBuffer, m_ptFirstCard->pucRead, sizRead);
			// advance the read pointer
			m_ptFirstCard->pucRead += sizRead;
		}
	}
	else
	{
		// the first card is not used by the write part

		// get the number of bytes left in this card
		sizRead = m_ptFirstCard->pucEnd - m_ptFirstCard->pucRead;
		if( sizRead>sizBufferSize )
		{
			sizRead = sizBufferSize;
		}
		// card can be empty for overlapping buffer grow
		if( sizRead>0 )
		{
			// copy the data
			memcpy(pucBuffer, m_ptFirstCard->pucRead, sizRead);
			// advance the read pointer
			m_ptFirstCard->pucRead += sizRead;
		}
		// reached the end of the buffer?
		if( m_ptFirstCard->pucRead>=m_ptFirstCard->pucEnd )
		{
			// card is empty, move on to next card
			ptNewCard = m_ptFirstCard->ptNext;
			if( ptNewCard!=NULL )
			{
				// remember the empty card
				ptOldCard = m_ptFirstCard;
				// move to the new first card
				m_ptFirstCard = ptNewCard;
				// delete the empty card
				delete ptOldCard;
			}
		}
	}

	return sizRead;
}


size_t romloader_usb_device::getCardSize(void) const
{
	size_t sizData;
	tBufferCard *ptCard;


	sizData = 0;
	ptCard = m_ptFirstCard;
	while( ptCard!=NULL )
	{
		if( ptCard->pucWrite==NULL )
		{
			sizData += m_ptFirstCard->pucEnd - m_ptFirstCard->pucRead;
		}
		else
		{
			sizData += m_ptFirstCard->pucWrite - m_ptFirstCard->pucRead;
		}
		ptCard = ptCard->ptNext;
	}

	return sizData;
}


void romloader_usb_device::flushCards(void)
{
	tBufferCard *ptOldCard;
	tBufferCard *ptNextCard;


	while( m_ptFirstCard!=NULL )
	{
		if( m_ptFirstCard->pucWrite!=NULL )
		{
			/* Skip all data in this card. */
			m_ptFirstCard->pucRead = m_ptFirstCard->pucWrite;
			/* This must be the last card. */
			break;
		}
		else
		{
			/* The card is not used by the write part. */
			ptNextCard = m_ptFirstCard->ptNext;
			if( ptNextCard!=NULL )
			{
				/* Remember the empty card. */
				ptOldCard = m_ptFirstCard;
				/* Move to the new first card. */
				m_ptFirstCard = ptNextCard;
				/* Delete the empty card. */
				delete ptOldCard;
			}
		}
	}
}


bool romloader_usb_device::expect_string(const char *pcString)
{
	unsigned char *pucBuffer;
	size_t sizString;
	size_t sizReceived;
	const unsigned int uiTimeoutMs = 200;
	bool fFound;


	/* Allocate a buffer for the string. */
	sizString = strlen(pcString);
	pucBuffer = new unsigned char[sizString];

	/* Receive data. */
	sizReceived = usb_receive(pucBuffer, sizString, uiTimeoutMs);
	fFound  = true;
	fFound &= (sizReceived==sizString);
	fFound &= ( memcmp(pucBuffer, pcString, sizString)==0 );

	delete pucBuffer;

	return fFound;
}


bool romloader_usb_device::parse_hex_digit(size_t sizDigits, unsigned long *pulResult)
{
	unsigned char *pucBuffer;
	unsigned long ulResult;
	bool fOk;
	unsigned char uc;
	unsigned int uiDigit;
	size_t sizCnt;
	size_t sizReceived;
	const unsigned int uiTimeoutMs = 200;


	/* Allocate a buffer for the digits. */
	pucBuffer = new unsigned char[sizDigits];

	/* Receive data. */
	sizReceived = usb_receive(pucBuffer, sizDigits, uiTimeoutMs);
	if( sizReceived!=sizDigits )
	{
		/* Not enough chars received. */
		fOk = false;
	}
	else
	{
		ulResult = 0;
		fOk = true;
		sizCnt = 0;
		while( sizCnt<sizDigits )
		{
			uc = pucBuffer[sizCnt];
			if( uc>='0' && uc<='9' )
			{
				uiDigit = uc - '0';
			}
			else if( uc>='a' && uc<='f' )
			{
				uiDigit = uc - 'a' + 10;
			}
			else if( uc>='A' && uc<='F' )
			{
				uiDigit = uc - 'A' + 10;
			}
			else
			{
				fOk = false;
				break;
			}
			ulResult <<= 4;
			ulResult |= uiDigit;

			++sizCnt;
		}

		if( fOk==true )
		{
			if( pulResult!=NULL )
			{
				*pulResult = ulResult;
			}
		}
	}

	return fOk;
}


void romloader_usb_device::hexdump(const unsigned char *pucData, unsigned long ulSize)
{
	const unsigned char *pucDumpCnt, *pucDumpEnd;
	unsigned long ulAddressCnt;
	size_t sizBytesLeft;
	size_t sizChunkSize;
	size_t sizChunkCnt;


	// show a hexdump of the data
	pucDumpCnt = pucData;
	pucDumpEnd = pucData + ulSize;
	ulAddressCnt = 0;
	while( pucDumpCnt<pucDumpEnd )
	{
		// get number of bytes for the next line
		sizChunkSize = 16;
		sizBytesLeft = pucDumpEnd - pucDumpCnt;
		if( sizChunkSize>sizBytesLeft )
		{
			sizChunkSize = sizBytesLeft;
		}

		// start a line in the dump with the address
		printf("%08lX: ", ulAddressCnt);
		// append the data bytes
		sizChunkCnt = sizChunkSize;
		while( sizChunkCnt!=0 )
		{
			printf("%02X ", *(pucDumpCnt++));
			--sizChunkCnt;
		}
		// next line
		printf("\n");
		ulAddressCnt += sizChunkSize;
	}
}
