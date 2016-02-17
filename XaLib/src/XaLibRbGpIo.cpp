#include <XaLibRbGpIo.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef _WIN32
#else
	#include <termios.h>
#endif

XaLibRbGpIo::XaLibRbGpIo() {

};

#ifdef _WIN32

#else

int XaLibRbGpIo::GpIoSet(const int& GpIoNumber,const string& GpIoDirection ,const int& GpIoValue){

	int ReturnValue=-1;

	int Export=GpIoExport(GpIoNumber);
	int Direction=GpIoSetDirection(GpIoNumber,GpIoDirection);
	int Value=GpIoSetValue(GpIoNumber,GpIoValue);

	if (Export==-1 || Direction==-1 || Value==-1) {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Setting Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));

		ReturnValue=-1;

	} else {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Set Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));

		ReturnValue=1;
	}

	return ReturnValue;
}

string XaLibRbGpIo::GpIoGet(const int& GpIoNumber) {
	
	string ReturnValue="-1";

	int Export=GpIoExport(GpIoNumber);
	
	if (Export==1) {

		ReturnValue=GpIoGetValue(GpIoNumber);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Get Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +ReturnValue);
		
	} else {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Error Getting Value From GpIo -> Number: " +FromIntToString(GpIoNumber));

	}
	
	return ReturnValue;
}

int XaLibRbGpIo::GpIoConfigure(const int& GpIoNumber,const string& GpIoDirection) {

	int ReturnValue=-1;

	int Export=GpIoExport(GpIoNumber);
	int Direction=GpIoSetDirection(GpIoNumber,GpIoDirection);

	
	if (Export==-1 || Direction==-1) {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Configuring GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Direction: " +GpIoDirection);

		ReturnValue=-1;

	} else {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Configuring GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Direction: " +GpIoDirection);

		ReturnValue=1;
	}

	return ReturnValue;
}

int XaLibRbGpIo::GpIoExport(const int& GpIoNumber) {

	char buf[11]; 

	int fd = open("/sys/class/gpio/export", O_WRONLY);

	sprintf(buf, "%d", GpIoNumber); 

	write(fd, buf, strlen(buf));

	close(fd);
    return 1;
}

int XaLibRbGpIo::GpIoUnexport(const int& GpIoNumber) {

	int ReturnValue=-1;
    string UnexportFile = "/sys/class/gpio/unexport";
    ofstream UnexportStream(UnexportFile.c_str());
	
	if (UnexportStream.is_open()) {

		UnexportStream << GpIoNumber;
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Unexporting GpIo -> Number: " +FromIntToString(GpIoNumber));

		ReturnValue=1;
	
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Unexporting GpIo -> Number: " +FromIntToString(GpIoNumber));

		ReturnValue=-1;
	}
    
    UnexportStream.close();

    return ReturnValue;
}
 
int XaLibRbGpIo::GpIoSetDirection(const int& GpIoNumber,const string& GpIoDirection) {
 
	int ReturnValue=-1;

    string DirectionFile ="/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/direction";
    ofstream DirectionStream(DirectionFile.c_str());

	if (DirectionStream.is_open()) {
	
		DirectionStream << GpIoDirection;
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Set Direction From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Direction: " +GpIoDirection);
		ReturnValue=1;
		 
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Setting Direction From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Direction: " +GpIoDirection);
		ReturnValue=-1;
	}

	DirectionStream.close();
	return ReturnValue;;
}
 
int XaLibRbGpIo::GpIoSetValue(const int& GpIoNumber,const int& GpIoValue) {
	
	int ReturnValue=-1;
    string GpIoValueFile = "/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/value";
    ofstream GpIoValueStream(GpIoValueFile.c_str());

	
	if (GpIoValueStream.is_open()){

		GpIoValueStream << GpIoValue ;
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Set Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));
		ReturnValue=1;
		
	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Setting Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +FromIntToString(GpIoValue));
		ReturnValue=-1;

	}

	GpIoValueStream.close();
	return ReturnValue;
}
 
string XaLibRbGpIo::GpIoGetValue(const int& GpIoNumber){

	string GpIoValue;
	string GpIoValueFile = "/sys/class/gpio/gpio" + FromIntToString(GpIoNumber) + "/value";
	ifstream GpIoValueStream(GpIoValueFile.c_str());

	if (GpIoValueStream.is_open()){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Get Value From GpIo -> Number: " +FromIntToString(GpIoNumber)+ " :: "+ "Value: " +GpIoValue);
		GpIoValueStream >> GpIoValue;

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Getting Value From GpIo -> Number: " +FromIntToString(GpIoNumber));
		GpIoValue="-1";
	}

	GpIoValueStream.close();
	return GpIoValue;
};
#endif

XaLibRbGpIo::~XaLibRbGpIo() {
}