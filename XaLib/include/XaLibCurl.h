#ifndef XALIBCURL_H
#define XALIBCURL_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>

#include <curl/curl.h>

extern XaLibLog LOG;

class XaLibCurl : protected XaLibBase {

	private:

		void* curl;

	protected:

	public:

		string Call(const string& url);

		XaLibCurl();
		~XaLibCurl();

		//typedef size_t(*CURL_WRITEFUNCTION_PTR)(void*, size_t, size_t, void*);

		//static int writer(char *data, size_t size, size_t nmemb,std::string *writerData);
		//static size_t handle(char * data, size_t size, size_t nmemb, string * p);
    	//size_t handle_impl(char * data, size_t size, size_t nmemb);

		//string MakeCall(const string& Url,const int& Ssl=0);
		//string MakeCall1(const string& Url,const int& Ssl=0);

    	//string GetCurlResponse();
};
#endif
