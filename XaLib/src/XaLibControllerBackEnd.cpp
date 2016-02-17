#include <XaLibControllerBackEnd.h>

XaLibControllerBackEnd::XaLibControllerBackEnd() {
};

void XaLibControllerBackEnd::OnStart(const string& ConfFile) {

	try {

		LoadXmlConfFile(ConfFile);
		StartLog();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"########################### STARTING BACK END ACTION LOG ############################");

		StartDb();
		StartHttp();

		SESSION.BackEndIp=HTTP.GetServerIpAddress();
		SESSION.FrontEndIp=HTTP.GetClientIpAddress();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Back End Server -> "+SESSION.BackEndIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Front End Server -> "+SESSION.FrontEndIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " + REQUEST.HeadersString);

	} catch (int e) {

		throw;
	}
};


/*
void XaLibController::GetClientInfo(){

	REQUEST.ClientIpAddress=HTTP.GetClientIpAddress();

	//LOG.SetIpAddress(REQUEST.ClientIpAddress);

	string Language=HTTP.GetHttpParam("l");

    if (Language=="NoHttpParam"){

		REQUEST.Language=SETTINGS["DefaultLanguage"];

    } else {

		REQUEST.Language=Language;
	}

	string Device=HTTP.GetHttpParam("d");

    if (Device=="NoHttpParam"){

		REQUEST.Device=SETTINGS["DefaultDevice"];

    } else {

		REQUEST.Device=Device;
	}

};*/

int XaLibControllerBackEnd::ProfileCalledObject(const string& CalledObject,const string& CalledEvent){
/*
	int ReturnStatus=0;

	XaUserProfile UserProfile;

	if (UserProfile.EventIsFree(CalledObject,CalledEvent)==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access FREE -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		ReturnStatus=1;

	} else {

		if(UserProfile.EventProfile(CalledObject,CalledEvent)==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
			ReturnStatus=1;

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"REFUSED Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		}
	}

	return ReturnStatus;
 */
};

void XaLibControllerBackEnd::SendResponse(){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"RESPONSE="+RESPONSE.Content);

		SendHeaders(RESPONSE.ResponseType);
		cout<<"<WsData><token>"+SESSION.Token+"</token>"+RESPONSE.Content+"</WsData>"<<endl;
};

XaLibControllerBackEnd::~XaLibControllerBackEnd() {
};