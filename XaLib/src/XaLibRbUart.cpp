#include <XaLibRbUart.h>

#include <sys/stat.h>
#include <fcntl.h>

#ifdef _WIN32
#else
	#include <termios.h>
#endif

/*
std::string cmd = "sudo chmod a+x file";
int r = system(cmd.c_str());
*/

XaLibRbUart::XaLibRbUart() {
};

string XaLibRbUart::SendReceive(const string &MsgString) {

#define TXBUFFER 10
#define RXBUFFER 10

string RbUartResponse="NoUartResponse";

#ifdef _WIN32
#else

	int uart0_filestream = -1;
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);

	if (uart0_filestream == -1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Unable to open UART");
	}

	struct termios options;
	
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;	
	options.c_iflag = IGNPAR | ICRNL;
	options.c_oflag = 0;
	options.c_lflag = 0;

	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);

#endif

	unsigned char tx_buffer[TXBUFFER];
	unsigned char *p_tx_buffer;

	p_tx_buffer = &tx_buffer[0];

	int MsgStringSize=MsgString.size();

	for (int a=0;a<=MsgStringSize;a++) {

        *p_tx_buffer++=MsgString[a];
    }

#ifdef _WIN32
#else

	if (uart0_filestream != -1){

		int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));

		if (count < 0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"UART TX Error");

		}
	}

	if (uart0_filestream != -1) {
		
		unsigned char rx_buffer[RXBUFFER+1];
		int rx_length = read(uart0_filestream, (void*)rx_buffer, RXBUFFER);

		
		if (rx_length < 0) {

		} else if (rx_length == 0) {

		} else {

			rx_buffer[rx_length] = '\0';
			stringstream ss;
			string s;
			ss << rx_buffer;
			ss >> s;

			RbUartResponse=s;
		}
	}

	close(uart0_filestream);
	#endif
	return RbUartResponse;
};

string XaLibRbUart::Send() {

#define TXBUFFER 10

string RbUartResponse="NoUartResponse";

#ifdef _WIN32
#else
/*
	int uart0_filestream = -1;
	uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);

	if (uart0_filestream == -1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Unable to open UART");
	}

	struct termios options;
	
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;	
	options.c_iflag = IGNPAR | ICRNL;
	options.c_oflag = 0;
	options.c_lflag = 0;

	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
*/
#endif
/*
	unsigned char tx_buffer[TXBUFFER];
	unsigned char *p_tx_buffer;

	p_tx_buffer = &tx_buffer[0];

	int MsgStringSize=MsgString.size();

	for (int a=0;a<=MsgStringSize;a++) {

        *p_tx_buffer++=MsgString[a];
    }
*/
#ifdef _WIN32
#else
/*
	if (uart0_filestream != -1){

		int count = write(uart0_filestream, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));

		if (count < 0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"UART TX Error");

		}
	}

	if (uart0_filestream != -1) {
		
		unsigned char rx_buffer[RXBUFFER+1];
		int rx_length = read(uart0_filestream, (void*)rx_buffer, RXBUFFER);

		
		if (rx_length < 0) {

		} else if (rx_length == 0) {

		} else {

			rx_buffer[rx_length] = '\0';
			stringstream ss;
			string s;
			ss << rx_buffer;
			ss >> s;

			RbUartResponse=s;
		}
	}

	close(uart0_filestream);
 */
	#endif
//	return RbUartResponse;

};
XaLibRbUart::~XaLibRbUart() {
}
