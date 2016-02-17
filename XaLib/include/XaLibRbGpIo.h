#ifndef XALIBRBGPIO_H
#define XALIBRBGPIO_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;

class XaLibRbGpIo : protected XaLibBase {

	public:

		XaLibRbGpIo();
		~XaLibRbGpIo();

		int GpIoConfigure(const int& GpIoNumber,const string& GpIoDirection);
		int GpIoSet(const int& GpIoNumber,const string& GpIoDirection,const int& GpIoValue);
		string GpIoGet(const int& GpIoNumber);

	protected:

	private:

		int GpIoExport(const int& GpIoNumber);
    	int GpIoUnexport(const int& GpIoNumber);
    	int GpIoSetDirection(const int& GpIoNumber,const string& GpIoDirection);
    	int GpIoSetValue(const int& GpIoNumber,const int& GpIoValue);
		string GpIoGetValue(const int& GpIoNumber);

};
 
#endif
