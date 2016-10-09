#include <Controller.h>
#include <XaLibControllerBackEnd.h>
#include <XaLibError.h>

/*
* General System Post or Get Parameters 
* @param do=action
* @param obj=object
* @param evt=event
* @param lay=layout
* @param l=language
* @param b=brand
* @param d=device type - pc tablet smartphone
*/

/*
&ReqType=xml
&Encoding=B64, no
&Encryption=yes;
&Data=;
&ResType=xml;
&ConsumerId=3;
&token=9879879
*/

/**** APPLICATION ****/
#include <XaUserLogin.h>
//#include <XaOuType.h>
//#include <XaOu.h>
//#include <XaUser.h>

#include <RpReqMatching.h>


//#include <XaLabel.h>
//#include <XaLanguage.h>
#include <XaDomain.h>
//#include <XaCurrency.h>
//#include <XaUserRole.h>
//#include <XaUserProfile.h>
//#include <XaLibRbGpIo.h>
#include <XaLibWs.h>

int main (void) {

    string ConfigurationFile {"../config/XaReq.xml"};

    unique_ptr<FILE, int(*)(FILE*)> fp(fopen(ConfigurationFile.c_str(), "r"), fclose);

    if (fp) {

            Controller ControllerObj(ConfigurationFile.c_str());

    } else {

            cout<< "Content-Type: text/html; charset=utf-8\n\n";
            cout<< "Configuration file doesn't exist -> "+ConfigurationFile<<endl;
    }

    return 0;
};

Controller::Controller(string ConfFile) {

    auto start = chrono::steady_clock::now();

    try {

            OnStart(ConfFile);
            DispatchWs();

    } catch (int e) {

            XaLibError Error;
            string ErrorDesc=Error.GetError(e);

            SendHtmlHeaders();
            cout<<"<WsData><error><number>"+FromIntToString(e)+"</number><description>"+ErrorDesc+"</description></error></WsData>"<<endl;

    } catch (...) {

            SendHtmlHeaders();
            cout<<"Generic not handled Error"<<endl;
    }

    auto diff = chrono::steady_clock::now() - start;
    string duration=to_string(chrono::duration <double, std::milli> (diff).count());

    LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Action Execution Time In Ms -> "+duration);

    //////VERIFICARE QUESTO CLOSE
    LOG.Close();
};

void Controller::DispatchWs () {

	XaLibWs Ws;
	Ws.Setup();

	REQUEST.CalledObject=Ws.GetObject();
	REQUEST.CalledEvent=Ws.GetEvent();
	SESSION.Token=Ws.GetToken();

	RESPONSE.ResponseType=Ws.GetResType();
	RESPONSE.ResponseLang=Ws.GetResLang();

	if (REQUEST.CalledObject=="XaReq" || REQUEST.CalledEvent=="Login") {
		/* In Case of Login I do not check the Token validity */
		REQUEST.HeadersString.append("&username="+Ws.GetUsername()+"&password="+Ws.GetPassword());

	} else {
		/* Token Validation */
		SESSION.XaUser_ID=XaLibToken::ValidateToken(SESSION.Token);
	}

	SESSION.ClientIp=Ws.GetClientIp();

	this->ExecuteWs(Ws);
	Ws.AddResponseLog();
	this->SendResponse();
};

void Controller::ExecuteWs(XaLibWs& Ws){

    if(REQUEST.CalledObject=="XaUserLogin") {
            unique_ptr<XaUserLogin> UserLogin (new XaUserLogin());
            UserLogin->Execute();
    }else if(REQUEST.CalledObject=="RpReqMatching") {

        unique_ptr<RpReqMatching> ReqMatching (new RpReqMatching());
        ReqMatching->Execute();

    }else if(REQUEST.CalledObject=="XaDomain") {

        unique_ptr<XaDomain> Domain (new XaDomain());
        Domain->Execute();

    }else {

        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Called Object Doesn't Exist -> "+REQUEST.CalledObject);
        throw 119;
    }
};

Controller::~Controller(){
};