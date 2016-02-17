#ifndef XALIBHTTP_H
#define XALIBHTTP_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaSettings SETTINGS;

class XaLibHttp : private XaLibBase {

	private:
		string HTTP_COOKIE;
		string HTTP_COMSPEC;
		string HTTP_DOCUMENT_ROOT;
		string HTTP_GATEWAY_INTERFACE;
		string HTTP_ACCEPT;
		string HTTP_ACCEPT_ENCODING;
		string HTTP_ACCEPT_LANGUAGE;
		string HTTP_CONNECTION;
		string HTTP_HOST;
		string HTTP_USER_AGENT;
		string HTTP_PATH;
		string HTTP_QUERY_STRING;
		string HTTP_CONTENT_LENGTH;
		string HTTP_REMOTE_ADDR;
		string HTTP_REMOTE_PORT;
		string HTTP_REQUEST_METHOD;
		string HTTP_REQUEST_URI;
		string HTTP_SCRIPT_FILENAME;
		string HTTP_SCRIPT_NAME;
		string HTTP_SERVER_ADDR;
		string HTTP_SERVER_ADMIN;
		string HTTP_SERVER_NAME;
		string HTTP_SERVER_PORT;
		string HTTP_SERVER_PROTOCOL;
		string HTTP_SERVER_SIGNATURE;
		string HTTP_SERVER_SOFTWARE;
		string HTTP_X_FORWARDED_FOR;

		void GetHttpHeaders();
        //string __getHeaders(string HttpHeaderName);

	protected:

	public:
            XaLibHttp();
            ~XaLibHttp();
            string RemoveCookie();
            string SetCookie();

            string GetHttpParam(string HttpParamName);
            vector<string>  GetHttpParamArray(string HttpParamName);
            vector<string>  GetHttpParamStruct(string HttpParamName,string StructType);
            string GetHttpHeadersString();
            string GetSessionId();
            string GetClientIpAddress ();
            string GetServerIpAddress ();
            string GetSecWebSocketKey();
};
#endif
