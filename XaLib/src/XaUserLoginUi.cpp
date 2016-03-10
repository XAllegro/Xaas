#include <XaUserLoginUi.h>
#include <XaLibAction.h>

XaUserLoginUi::XaUserLoginUi() {
};

void XaUserLoginUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="LoginFrm"){
		this->LoginFrm();
	} else if (CalledEvent=="Login"){
		this->Login();
	} else if (CalledEvent=="Logout"){
		this->Logout();
	} else if (CalledEvent=="LogoutFrm"){
		this->LogoutFrm();
	} else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserLoginUi::LoginFrm () {

	vector<string> Templates=SetPageLayout("standalone");
	Templates.push_back("XaUserLoginFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),{},{},{},0);
	
};

void XaUserLoginUi::Login (){

	string StrUsername=HTTP.GetHttpParam("username");
	string StrPassword=HTTP.GetHttpParam("password");

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCallLogin(StrUsername,StrPassword));
	CheckResponse(CallResponse);
	
	
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromString(CallResponse);
	string token=XaLibDom::GetElementValueByXPath(XmlDomDoc,"/WsData/token");

	if ( token=="ELEMENT-NOT-DEFINED" || token=="" || token.size()<FromStringToInt(SETTINGS["SessionIdLength"])) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Back End Login Action returned an error");

		RESPONSE.ResponseType="location";
		RESPONSE.Location="obj=XaUserLoginUi&evt=LoginFrm";

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Back End Login Affected returned a token");
		
		SESSION.Token=token;
		RESPONSE.ResponseType="location";
		RESPONSE.Location="obj=XaPages&evt=XaMyPage";
		RESPONSE.Content=CallResponse;
		
		
		//se la risposta e un errore manda con un variabile per gestirlo
		
	}
};

void XaUserLoginUi::Logout (){

	XaLibCurl LibCurl;
	string CallResponse= LibCurl.Call(BuildBackEndCall("XaUserLogin","Logout",{},{}));

	RESPONSE.ResponseType="location";
	RESPONSE.Location="obj=XaUserLoginUi&evt=LogoutFrm";
	RESPONSE.Content="";
};

void XaUserLoginUi::LogoutFrm () {

	vector<string> Templates=SetPageLayout("standalone");
	Templates.push_back("XaUserLogoutFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),{},{},{},0);
};

XaUserLoginUi::~XaUserLoginUi(){
};