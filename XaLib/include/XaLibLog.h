#ifndef XALIBLOG_H
#define XALIBLOG_H

#include <XaLibBase.h>
#include <XaLibDb.h>

extern unique_ptr<ofstream> MY_LOG_FILE;
extern XaLibDb DB_LOG;
extern XaSession SESSION;

class XaLibLog : protected XaLibBase {

	private:

		void Rotate();

	protected:

	public:

		XaLibLog();
		~XaLibLog();

		void Write(const string& LogMessageLevel, const char* ClassName, const char* MethodName,const int& LineNumber,const string& LogMessage);
		void WriteDb (const string& LogMessageLevel,const char* ClassName,const char* MethodName,const string& LineNumber,const string& LogMessage);
		void WriteFile (string MyLogString,string LogMessageLevel);

		void Close();

};
#endif