#ifndef XALIBRBUART_H
#define XALIBRBUART_H

//! XaLibRbUart -> XaLib Raspberry Uart class.

/*!
Implementation of Uart comunication with Raspberry

Linux Operation:
1)
sudo vi /boot/cmdline.txt
replace-> dwc_otg.lpm_enable=0 console=ttyAMA0,115200 kgdboc=ttyAMA0,115200 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait
with   -> dwc_otg.lpm_enable=0 console=tty1 root=/dev/mmcblk0p2 rootfstype=ext4 elevator=deadline rootwait

2)
sudo vi /etc/inittab
comment -> T0:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100

3)
sudo shutdown -r now

4)
in rc.local
sudo chmod a+rw /dev/ttyAMA0

5)
sudo chmod 666 /dev/ttyAMA0

6)
PIN CONFIGURATION

pin 14 -> UART0_TXD
pin 15 -> UART0_RXD


OPTIONS
O_RDONLY - Open for reading only.
O_RDWR - Open for reading and writing.
O_WRONLY - Open for writing only.
O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
if there is no input immediately available (instead of blocking). Likewise, write requests can also return
immediately with a failure status if the output can't be written immediately.

O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.

CONFIGURE THE UART

The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
CSIZE:- CS5, CS6, CS7, CS8
CLOCAL - Ignore modem status lines
CREAD - Enable receiver
IGNPAR = Ignore characters with parity errors
ICRNL - Map CR to NL on input
PARENB - Parity enable
PARODD - Odd parity (else even)

TEST WITH MINICOM
sudo apt-get install minicom
minicom -b 9600 -o -D /dev/ttyAMA0
*/


#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;

class XaLibRbUart : public XaLibBase {

	public:
		XaLibRbUart();

		string SendReceive(const string &MsgString);
		string Send();

		
		~XaLibRbUart();

	protected:

	private:
};
 
#endif
