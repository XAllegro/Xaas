#ifndef XALIBBASE_H
#define XALIBBASE_H

#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <stdexcept>
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <thread>
#include <future>
#include <unistd.h>
#include <memory>
#include <random>
#include <iomanip>
#include <tuple>

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
#endif

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/globals.h>

#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include <libexslt/exslt.h>

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/conf.h>

using namespace std;

struct XaSession {

    string Token="";
    int XaUser_ID=0;
    int XaWsSession_ID=0;
    string BackEndIp="";
    string FrontEndIp="";
    string ClientIp="";    
};

struct XaRequest {

    string CalledLayout="";
    string CalledObject="";
    string CalledEvent="";
    string HeadersString="";
    string HeadersStringCustom="";
    string Language="";
};

struct XaResponse {

    string Location;
    string Content;
    string ResponseType;
    string ResponseLang;
};

typedef map<string, string> XaSettings;

#if defined(__CYGWIN32__) ||  defined(__CYGWIN__) ||  defined(__MSYS__)
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
#else
#endif

class XaLibBase {

    private:

    protected:

        typedef map<int, map<string,string> > DbResMap;
        typedef map<int, map<string,string> > FieldsMap;

        int PositionInVector(vector<string>& SearchOn,const string& SearchFor);
        string FromIntToString(int IntValue);
        int FromStringToInt(const string& StringValue);
        unsigned int FromHexStringToUnsignedInt(string StringValue);

        string FromFloatToString(float FloatValue);
        float FromStringToFloat(string StringValue);

        string FromDoubleToString(double DoubleValue);
        double FromStringToDouble(string StringValue);

        string FromCharToString(char CharValue);
        string FromCharArrayToString(char CharValue[]);
        char* FromStringToCharArray(string StringValue);
        string FromStringToHex(const string& StringValue,int CapitalCase);
        int FromCharToInt(char CharValue);

        vector<string> FromCsvStringToVector(string& CsvString);

        void SendHtmlHeaders();

    public:

        XaLibBase();
        virtual ~XaLibBase();
};
#endif
