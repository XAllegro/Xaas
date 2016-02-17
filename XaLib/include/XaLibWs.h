#ifndef XALIBWS_H
#define XALIBWS_H

#include <XaLibSql.h>

//extern XaSettings SETTINGS;
//extern XaRequest REQUEST;
//extern XaResponse RESPONSE;


/**
 * @brief Web Services Implementation
 *
 * @details Web Services Implementation:
 * Manage the Web Service life cycle 
 *
 * @see XaLibBase
 * @see XaLibControllerBackEnd
 * 
 * @see alex@xallegro.com
 * @author Alessandro Mariotti - alex@xallegro.com
*/

class XaLibWs : protected XaLibBase {

    private:

        string ReqType={""};
        string Encoding={""};
        string Encryption={""};

        string ConsumerId={""};
        string ConsumerIp={""};
        string ConsumerHostname={""};

        /* 32B key*/
        string ConsumerKey={""};

        string ResType={""};
        string ResLang={""};
        string Data={""};

        string Username={""};
        string Password={""};

        /* 32B Token*/
        string Token={""};

        string ClientIp={""};

        string Object={""};
        string Event={""};

        int WsId;

        map <int, map<string,string> > Params;

        /**
        * Check the required parameter for a standard Web Service Call\n
        * The required parameter for a standard Web Service Call are:\n
        * Data
        * ReqType
        * Encoding
        * Encryption
        * ConsumerId
        * ResType
        *
        * @return Void
        *
        */
        void CheckRequired();
        void GetEncodedData();
        void GetConsumer();
        void GetDecryptedData();

        void AddRequestLog();

        void ExtractData();
        
        map <int, map<string,string> > GetParams();

    protected:

    public:

        void Setup();

        string GetObject();
        string GetEvent();
        string GetUsername();
        string GetPassword();
        string GetToken();
        string GetClientIp();
        string GetResType();
        string GetResLang();

        int GetWsId();

        void AddResponseLog();

        //int CheckCaller(const string &CallerName,const string &CallerKey);
        XaLibWs();
        ~XaLibWs();
};
#endif