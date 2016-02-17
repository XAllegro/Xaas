#include <XaLibLog.h>
#include <XaLibBase.h>
#include <XaLibTime.h>
#include <XaLibSql.h>
mutex m;
extern XaLibDb DB_LOG;

XaLibLog::XaLibLog(){
};

/**
* Instance of ofstream 
* @param LogFilePath - string - complete log file path
* @param SysLogLevelConf - string - log level indicated in conf file - 0:nothing 1:all 2:error only
* @see 
* @return MyLogFile - ofstream
*/

//LIVELLI DI LOG: 0=NIENTE 1=TUTTO 2=SOLO ERR
void XaLibLog::Write(const string& LogMessageLevel,const char* ClassName,const char* MethodName,const int& LineNumber,const string& LogMessage){

	stringstream LineNumberStringStream;
	LineNumberStringStream << LineNumber;
	string LineNumberString= LineNumberStringStream.str();

	if (SETTINGS["LogLevel"]=="0"){

	} else {

		if (SETTINGS["LogUseDb"]=="yes" && SETTINGS["DatabaseEnable"]=="yes") {

			WriteDb(LogMessageLevel,ClassName,MethodName,LineNumberString,LogMessage);

		} else {

			unique_ptr<XaLibTime> LibTimeLocal(new XaLibTime());
			string LogTime=LibTimeLocal->GetDateTimeIsoComplete();

			string MyLogString="["+SETTINGS["AppName"]+"]["+LogMessageLevel+"]["+SESSION.FrontEndIp+"]["+LogTime+"]["+SESSION.ClientIp+ "]["+FromIntToString(SESSION.XaUser_ID)+"]["+ClassName +"]["+LineNumberString+"]["+MethodName+"]["+LogMessage+"]";

			WriteFile(MyLogString,LogMessageLevel);
		}
	}
};

//void XaLibLog::WriteFile (string MyLogString,string LogMessageLevel,mutex *m){

void XaLibLog::WriteDb (const string& LogMessageLevel,const char* ClassName,const char* MethodName,const string& LineNumber,const string& LogMessage){

	vector<string> VectorFields ={"app_name","log_level","server_ip_address","ip_address","XaUser_ID","class_name","method_name","line_number","message"}; 
	vector<string> VectorValues ={SETTINGS["AppName"],LogMessageLevel,SESSION.FrontEndIp,SESSION.ClientIp,FromIntToString(SESSION.XaUser_ID),ClassName,MethodName,LineNumber,LogMessage};

	if (SETTINGS["LogLevel"]=="1"){

		XaLibSql::Insert(DB_LOG,"XaSystemLog",VectorFields,VectorValues);

	} else if (SETTINGS["LogLevel"]=="2" && LogMessageLevel=="ERR"){

		XaLibSql::Insert(DB_LOG,"XaSystemLog",VectorFields,VectorValues);
	}
};


void XaLibLog::WriteFile (string MyLogString,string LogMessageLevel){

	if (SETTINGS["LogLevel"]=="1"){		

		m.lock();
		*MY_LOG_FILE<<MyLogString<<endl;
		m.unlock();

	} else if (SETTINGS["LogLevel"]=="2" && LogMessageLevel=="ERR"){

		m.lock();
		*MY_LOG_FILE<<MyLogString<<endl;
		m.unlock();

	}

};

void XaLibLog::Rotate(){

};

void XaLibLog::Close(){

	MY_LOG_FILE->close();
};

XaLibLog::~XaLibLog(){
};