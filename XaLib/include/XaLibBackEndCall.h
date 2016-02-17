#ifndef XALIBACTION_H
#define XALIBACTION_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>

//#include <XaLibWebSocket.h>

//SUPERGLOBALS VARIABLES

extern XaLibLog LOG;
//extern XaLibHttp HTTP;
//extern XaLibDb DB_SESSION;
//extern XaLibDb DB_READ;
//extern XaLibDb DB_WRITE;
//extern XaLibDb DB_LOG;

//extern XaSession SESSION;
//extern XaRequest REQUEST;
//extern XaResponse RESPONSE;
//extern XaSettings SETTINGS;

/**
 * @brief Parent Class for View actions
 *
 * @details Parent Class for View actions:
 * All action class inherit from this class
 *
 * @see XaLibBase
 * 
 * @see alex@xallegro.com
 * @author Alessandro Mariotti
*/

class XaLibBackEndCall : protected XaLibBase {

    private:

    protected:

    public:
        /**
        * Builds the XML for the Back End Call\n
        * The general structure is :\n
        * @code
        * <WsData>
        *   <login>
        *       <token>[TOKEN]</token>
        *   </login>
        *   <operation>
        *       <object>[OBJECT]</object>
        *       <event>[EVENT]</event>
        *   </operation>
        *   <params>
        *       <p>
        *           <n></n>
        *           <v></v>
        *       </p>
        *   </params>
        * </WsData>
        * @endcode
        * 
        * @param Object Back End Object to call
        * @param Event Back End Event to call
        * @param ParamName Parameter Names to send with the Call
        * @param ParamValue Parameter Values to send with the Call
        * 
        * @return string
        *
        * @code
        * BuildBackEndCall("XaUser", "Logout",{},{};
        * @endcode
        *
        */
        string BuildCall(const string& Object, const string& Event,const vector <string>& ParamName,const vector <string>& ParamValue);
        string BuildCallLogin(const string& Username, const string& Password);
        string BuildCallBase();
        string BuildCallSectionOperation(const string& Object, const string& Event);
        string BuildCallSectionParams(const vector<string>& Names, const vector<string>& Values);

        XaLibBackEndCall ();
	virtual ~XaLibBackEndCall ();

};
#endif
