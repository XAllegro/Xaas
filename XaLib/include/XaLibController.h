#ifndef XALIBCONTROLLER_H
#define XALIBCONTROLLER_H

#include <XaLibBase.h>
#include <XaLibHttp.h>
#include <XaLibConfig.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibDom.h>
#include <XaLibSql.h>
#include <XaLibChar.h>
#include <XaLibCrypto.h>
#include <XaLibMail.h>
#include <XaLibTime.h>
#include <XaLibCurl.h>
#include <XaLibWs.h>
#include <XaUserLogin.h>
/**
 * @brief Base Class for Controllrs
 *
 * @details Base Class for Controllrs:\n
 * 
 * Any Application Controller will extend from this class
 *
 * @see alex@xallegro.com
 * @author Alessandro Mariotti
*/
class XaLibController : protected XaLibBase {

    private:
    protected:

        /**
        * @brief Load Configuration File
        * @details Load Configuration File and pushes values in \n
        * a Super Global Variable map<string, string> XaSettings; 
        * 
        * @see XaLibBase
        * @param ConFile Configuration File - Relative or absolute path
        * @return Void
        *
        * Example Usage: in OnStart Method
        *
        * @code
        *	void XaLibController::OnStart(const string& ConfFile) {
        * 
        *		LoadXmlConfFile(ConfFile);
        *		...
        * 
        *	}
        * @endcode
        *
        */
        void LoadXmlConfFile(string ConfFile);
        void StartLog();
        void StartHttp();
        void StartDb();

        //void GetServerInfo();

        void SendHeaders(const string& HeadersType);	
        //void SendHeadersLocation(const string& Location);

        /*
        int OnStartStatus=1;
        void OnStart(const string& ConfFile);

        void LoadXmlConfFile(string ConfFile);
        void StartLog();	
        void StartHttp();
        void StartDb();

        int  ProfileCalledObject(const string& CalledObject,const string& CalledEvent);

        virtual void SendResponse();
        virtual void DispatchWs();
        void Dispatch();

        virtual void ExecuteCalledObject();

        void SendHeaders(string& HeadersType) const;

*/
    public:
/*
        void GetCall();
        void GetLayout();
        void GetServerInfo();
        void GetClientInfo();
        void GetWs();
*/
        XaLibController();
        virtual ~XaLibController();
	
};
#endif