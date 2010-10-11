/***************************************************************************
 *   Copyright (C) 2010 by Christoph Thelen                                *
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


#include "usbmon.h"

#include <stddef.h>
#include <string.h>

#include "serial_vectors.h"
#include "usb.h"
#include "usbmonitor_commands.h"


/*-----------------------------------*/


typedef union
{
	unsigned char *puc;
	unsigned short *pus;
	unsigned long *pul;
	unsigned long ul;
} ADR_T;


typedef void (*PFN_MONITOR_CALL_T)(unsigned long ulR0);


static unsigned char aucPacketRx[64];
static SERIAL_COMM_UI_FN_T tOldVectors;


/*-----------------------------------*/


static void usbmon_send_status(USBMON_STATUS_T tStatus)
{
	/* Write the status to the fifo. */
	usb_send_byte(tStatus);

	/* Send the packet. */
	usb_send_packet();
}


static void usbmon_read(unsigned long ulAddress, unsigned long ulSize, USBMON_ACCESSSIZE_T tAccessSize)
{
	ADR_T uAdrCnt;
	ADR_T uAdrEnd;
	unsigned long ulValue;
	int iCnt;


	/* Get the start address. */
	uAdrCnt.ul = ulAddress;
	/* Get the end address. */
	uAdrEnd.ul = ulAddress + ulSize;

	/* Write status "Ok" to the fifo. */
	usb_send_byte(USBMON_STATUS_Ok);

	/* Write data bytes to the fifo. */
	do
	{
		/* Get the next data element in the requested access width. */
		switch(tAccessSize)
		{
		case USBMON_ACCESSSIZE_Byte:
			ulValue = *(uAdrCnt.puc++);
			break;

		case USBMON_ACCESSSIZE_Word:
			ulValue = *(uAdrCnt.pus++);
			break;

		case USBMON_ACCESSSIZE_Long:
			ulValue = *(uAdrCnt.pul++);
			break;
		}

		/* Add the data byte-by-byte to the fifo. */
		iCnt = 1<<tAccessSize;
		do
		{
			usb_send_byte((unsigned char)(ulValue & 0xffU));
			ulValue >>= 8;
			--iCnt;
		} while( iCnt>0 );
	} while( uAdrCnt.ul<uAdrEnd.ul);

	/* Send the packet. */
	usb_send_packet();
}


static void usbmon_write(unsigned long ulAddress, unsigned long ulDataSize, USBMON_ACCESSSIZE_T tAccessSize)
{
	const unsigned char *pucCnt;
	const unsigned char *pucEnd;
	ADR_T uAdrDst;
	unsigned long ulValue;


	/* Get the source start address. */
	pucCnt = aucPacketRx + 5;
	/* Get the source end address. */
	pucEnd = aucPacketRx + 5 + ulDataSize;
	/* Get the destination end address. */
	uAdrDst.ul = ulAddress;

	/* Write data bytes to memory. */
	do
	{
		/* Get the next data element in the requested access width. */
		switch(tAccessSize)
		{
		case USBMON_ACCESSSIZE_Byte:
			*(uAdrDst.puc++) = *(pucCnt++);
			break;

		case USBMON_ACCESSSIZE_Word:
			ulValue  = *(pucCnt++);
			ulValue |= *(pucCnt++) << 8;
			*(uAdrDst.pus++) = (unsigned short)ulValue;
			break;

		case USBMON_ACCESSSIZE_Long:
			ulValue  = *(pucCnt++);
			ulValue |= *(pucCnt++) << 8;
			ulValue |= *(pucCnt++) << 16;
			ulValue |= *(pucCnt++) << 24;
			*(uAdrDst.pul++) = ulValue;
			break;
		}
	} while( pucCnt<pucEnd);

	/* Send the status packet. */
	usbmon_send_status(USBMON_STATUS_Ok);
}


static unsigned char netx10_serial_get(unsigned int uiHandle __attribute__((unused)))
{
	unsigned long ulFillLevel;
	unsigned char ucData;


	/* Wait for a byte in the fifo. */
	do
	{
		ulFillLevel = usb_get_rx_fill_level();
	} while( ulFillLevel!=0 );

	/* Get a byte from the fifo. */
	ucData = usb_get_byte();
	return ucData;
}


static void netx10_serial_put(unsigned int uiHandle __attribute__((unused)), unsigned int uiChar)
{
	unsigned long ulFillLevel;


	/* Add the byte to the fifo. */
	usb_send_byte((unsigned char)uiChar);

	/* Reached the maximum packet size? */
	ulFillLevel = usb_get_rx_fill_level();
	if( ulFillLevel>=sizeof(USBMON_PACKET_MESSAGE_T) )
	{
		/* Yes -> send the packet. */
		usb_send_packet();

		/* Start a new packet. */
		usb_send_byte(USBMON_STATUS_CallMessage);
	}
}


static unsigned int netx10_serial_peek(unsigned int uiHandle __attribute__((unused)))
{
	unsigned long ulFillLevel;


	ulFillLevel = usb_get_rx_fill_level();
	return (ulFillLevel==0) ? 0U : 1U;
}


static void netx10_serial_flush(unsigned int uiHandle __attribute__((unused)))
{
	usb_send_packet();
}


static const SERIAL_COMM_UI_FN_T tUsbCallConsole =
{
	.fn =
	{
		.fnGet = netx10_serial_get,
		.fnPut = netx10_serial_put,
		.fnPeek = netx10_serial_peek,
		.fnFlush = netx10_serial_flush
	}
};


static void usbmon_call(unsigned long ulAddress, unsigned long ulR0)
{
	PFN_MONITOR_CALL_T ptCall;


	ptCall = (PFN_MONITOR_CALL_T)ulAddress;

	/* Send the status packet. */
	usbmon_send_status(USBMON_STATUS_Ok);

	/* Save the old vectors. */
	memcpy(&tOldVectors, &tSerialVectors, sizeof(SERIAL_COMM_UI_FN_T));

	/* Set the vectors. */
	memcpy(&tSerialVectors, &tUsbCallConsole, sizeof(SERIAL_COMM_UI_FN_T));

	/* Start the new message packet. */
	usb_send_byte(USBMON_STATUS_CallMessage);

	/* Call the routine. */
	ptCall(ulR0);

	/* Flush any remaining bytes in the fifo. */
	usb_send_packet();

	/* Restore the old vectors. */
	memcpy(&tSerialVectors, &tOldVectors, sizeof(SERIAL_COMM_UI_FN_T));

	/* The call finished, notify the PC. */
	usbmon_send_status(USBMON_STATUS_CallFinished);
}


static unsigned long get_unaligned_dword(const unsigned char *pucBuffer)
{
	unsigned long ulValue;


	ulValue  = pucBuffer[0];
	ulValue |= pucBuffer[1]<<8U;
	ulValue |= pucBuffer[2]<<16U;
	ulValue |= pucBuffer[3]<<24U;

	return ulValue;
}


static int usbmon_process_packet(unsigned long ulPacketSize)
{
	USBMON_COMMAND_T tCmd;
	unsigned long ulDataSize;
	unsigned long ulAddress;
	USBMON_ACCESSSIZE_T tAccessSize;
	unsigned long ulR0;
	int iTerminate;


	/* Default is to keep running after the command. */
	iTerminate = 0;

	/* Get the command and the data size from the first byte. */
	tCmd = (USBMON_COMMAND_T)(aucPacketRx[0] >> 5U);
	ulDataSize = aucPacketRx[0] & 0x1fU;

	/* Get the address. */
	ulAddress = get_unaligned_dword(aucPacketRx + 1);

	if( tCmd==USBMON_COMMAND_Execute )
	{
		if( ulPacketSize!=9U )
		{
			usbmon_send_status(USBMON_STATUS_InvalidPacketSize);
		}
		else
		{
			ulR0 = get_unaligned_dword(aucPacketRx + 5);
			usbmon_call(ulAddress, ulR0);
		}
	}
	else if( tCmd==USBMON_COMMAND_Exit )
	{
		if( ulPacketSize!=1U )
		{
			usbmon_send_status(USBMON_STATUS_InvalidPacketSize);
		}
		else
		{
			/* This is a request to terminate the usb monitor. */
			usbmon_send_status(USBMON_STATUS_Ok);
			iTerminate = 1;
		}
	}
	else
	{
		tAccessSize = (USBMON_ACCESSSIZE_T)(tCmd&3);

		/* Distinguish read and write commands by bit 2.
		   NOTE: This works because read commands start at 0 and write
		         commands at 4. */
		if( (tCmd&4)==0 )
		{
			if( ulPacketSize!=5 )
			{
				usbmon_send_status(USBMON_STATUS_InvalidPacketSize);
			}
			else if( ulDataSize>31 )
			{
				usbmon_send_status(USBMON_STATUS_InvalidSizeParameter);
			}
			else
			{
				usbmon_read(ulAddress, ulDataSize, tAccessSize);
			}
		}
		else
		{
			if( ulPacketSize<6 )
			{
				usbmon_send_status(USBMON_STATUS_InvalidPacketSize);
			}
			else if( ulDataSize>27 )
			{
				usbmon_send_status(USBMON_STATUS_InvalidSizeParameter);
			}
			else
			{
				usbmon_write(ulAddress, ulDataSize, tAccessSize);
			}
		}
	}

	return iTerminate;
}


void usbmon_loop(void)
{
	unsigned long ulFillLevel;
	unsigned char *pucCnt;
	unsigned char *pucEnd;
	int iTerminate;


	/* start loopback */
	iTerminate = 0;
	while( iTerminate==0 )
	{
		/* wait for a character in the input fifo */

		/* get the Uart RX input fill level */
		ulFillLevel = usb_get_rx_fill_level();
		if( ulFillLevel>0 )
		{
			/* Is the fill level valid? */
			if( ulFillLevel>64 )
			{
				ulFillLevel = 64;
			}
			else
			{
				/* Copy the complete packet to the buffer. */
				pucCnt = aucPacketRx;
				pucEnd = aucPacketRx + ulFillLevel;
				do
				{
					*(pucCnt++) = usb_get_byte();
				} while( pucCnt<pucEnd );

				iTerminate = usbmon_process_packet(ulFillLevel);
			}
		}
	}
}
