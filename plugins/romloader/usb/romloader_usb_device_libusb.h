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


#ifndef __ROMLOADER_USB_DEVICE_LIBUSB_H__
#define __ROMLOADER_USB_DEVICE_LIBUSB_H__


#if ROMLOADER_USB_LIBUSB_VERSION==0
#	include <usb.h>

	typedef struct usb_device libusb_device;
	typedef usb_dev_handle libusb_device_handle;
	typedef void libusb_context;
#	ifdef _WIN64
		typedef __int64 ssize_t;
#	else
		typedef int ssize_t;
#	endif /* _WIN64 */

	enum libusb_error
	{
		LIBUSB_SUCCESS = 0,
		LIBUSB_ERROR_IO = -1,
		LIBUSB_ERROR_INVALID_PARAM = -2,
		LIBUSB_ERROR_ACCESS = -3,
		LIBUSB_ERROR_NO_DEVICE = -4,
		LIBUSB_ERROR_NOT_FOUND = -5,
		LIBUSB_ERROR_BUSY = -6,
		LIBUSB_ERROR_TIMEOUT = -116,
		LIBUSB_ERROR_OVERFLOW = -8,
		LIBUSB_ERROR_PIPE = -9,
		LIBUSB_ERROR_INTERRUPTED = -10,
		LIBUSB_ERROR_NO_MEM = -11,
		LIBUSB_ERROR_NOT_SUPPORTED = -12,
		LIBUSB_ERROR_OTHER = -99
	};

#else
#	include <libusb-1.0/libusb.h>
#endif

#include "romloader_usb_device.h"


#if defined(WIN32)
#	include <windows.h>
#endif


typedef struct usb_device_descriptor LIBUSB_DEVICE_DESCRIPTOR_T;


class romloader_usb_provider;
class romloader_usb_reference;

class romloader_usb_device_libusb : public romloader_usb_device
{
public:
	romloader_usb_device_libusb(const char *pcPluginId);
	~romloader_usb_device_libusb(void);

	const char *libusb_strerror(int iError);

	int detect_interfaces(romloader_usb_reference ***ppptReferences, size_t *psizReferences, romloader_usb_provider *ptProvider);
	int Connect(unsigned int uiBusNr, unsigned int uiDeviceAdr);
	void Disconnect(void);

	int execute_command(const unsigned char *aucOutBuf, size_t sizOutBuf, unsigned char *aucInBuf, size_t *psizInBuf);
	int receive_packet(unsigned char *aucInBuf, size_t *psizInBuf, unsigned int uiTimeoutMs);

protected:
	ROMLOADER_CHIPTYP m_tChiptyp;
	ROMLOADER_ROMCODE m_tRomcode;

	unsigned char m_ucEndpoint_In;
	unsigned char m_ucEndpoint_Out;

private:
	const NETX_USB_DEVICE_T *fIsDeviceNetx(libusb_device *ptDevice) const;

	libusb_device *find_netx_device(libusb_device **ptDeviceList, ssize_t ssizDevList, unsigned int uiBusNr, unsigned int uiDeviceAdr);
	int setup_netx_device(libusb_device *ptNetxDevice);

	int libusb_reset_and_close_device(void);
//	int libusb_release_and_close_device(void);


	/* General update routines. */
	int update_old_netx_device(libusb_device *ptNetxDevice, libusb_device **pptUpdatedNetxDevice);
	unsigned short crc16(const unsigned char *pucData, size_t sizData);
	/* netx10 update routines. */
	int netx10_discard_until_timeout(libusb_device_handle *ptDevHandle);
	int netx10_load_code(libusb_device_handle *ptDevHandle, const unsigned char *pucNetxCode, size_t sizNetxCode);
	int netx10_start_code(libusb_device_handle *ptDevHandle, const unsigned char *pucNetxCode);
	int netx10_upgrade_romcode(libusb_device *ptDevice, libusb_device **pptUpdatedNetxDevice);
	/* netx500 update routines. */
	int netx500_exchange_data(libusb_device_handle *ptDevHandle, const unsigned char *pucOutBuffer, unsigned char *pucInBuffer);
	int netx500_discard_until_timeout(libusb_device_handle *ptDevHandle);
	int netx500_load_code(libusb_device_handle *ptDevHandle, const unsigned char *pucNetxCode, size_t sizNetxCode);
	int netx500_start_code(libusb_device_handle *ptDevHandle, const unsigned char *pucNetxCode);
	int netx500_upgrade_romcode(libusb_device *ptDevice, libusb_device **pptUpdatedNetxDevice);

	const int m_iConfiguration;
	const int m_iInterface;



	static const char *m_pcPluginNamePattern;

	libusb_context *m_ptLibUsbContext;
	libusb_device_handle *m_ptDevHandle;

	static const char *m_pcLibUsb_BusPattern;
	static const char *m_pcLibUsb_DevicePattern;


	typedef struct
	{
		int iError;
		const char *pcMessage;
	} LIBUSB_STRERROR_T;
	static const LIBUSB_STRERROR_T atStrError[14];
};


#endif	/* __ROMLOADER_USB_DEVICE_LIBUSB_H__ */

