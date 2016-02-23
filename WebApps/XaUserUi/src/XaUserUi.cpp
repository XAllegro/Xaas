#include <XaUserUi.h>
#include <XaLibAction.h>

XaUserUi::XaUserUi() {
};

void XaUserUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="LoginFrm"){
		this->LoginFrm();
	} else if (CalledEvent=="Login"){
		this->Login();
	} else if (CalledEvent=="Logout"){
		this->Logout();
	} else if (CalledEvent=="LogoutFrm"){
		this->LogoutFrm();
	} else if (CalledEvent=="List"){
		this->List();
	} else if (CalledEvent=="Read"){
		this->Read();
	} else if (CalledEvent=="CreateFrm"){
		this->CreateFrm();
	} else if (CalledEvent=="Create"){
		this->Create();
	} else if (CalledEvent=="UpdateFrm"){
		this->UpdateFrm();
	} else if (CalledEvent=="Update"){
		this->Update();
	} else if (CalledEvent=="Delete"){
		this->Delete();
	} else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserUi::LoginFrm () {

	string StrError=HTTP.GetHttpParam("LoginStatus");
	SetLayout("LoginFrm");
	AddXmlFile("LoginFrm");
	AddXslFile("LoginFrm");

	AddXslParamCommon();

	if (StrError=="error") {

		AddXslParam("LoginStatus","error");
	}

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
};

void XaUserUi::Login (){

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
		RESPONSE.Location="obj=XaUserUi&evt=LoginFrm";

	} else {

		SESSION.Token=token;
		RESPONSE.ResponseType="location";
		RESPONSE.Location="obj=XaPages&evt=XaMyPage";
		RESPONSE.Content=CallResponse;	
	}
};

void XaUserUi::Logout (){

	XaLibCurl LibCurl;
	string CallResponse= LibCurl.Call(BuildBackEndCall("XaUser","Logout",{},{}));

	RESPONSE.ResponseType="location";
	RESPONSE.Location="obj=XaUserUi&evt=LogoutFrm";
	RESPONSE.Content="";
};

void XaUserUi::LogoutFrm () {

	SetLayout("LoginFrm");
	AddXmlFile("LogoutFrm");
	AddXslFile("LogoutFrm");

	AddXslParamCommon();

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
};

void XaUserUi::List () {

	AddJsVarFile("XaModel","XaUser");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	vector <string> FieldsValues ={};

	FieldsValues.push_back(HTTP.GetHttpParam("tree_parent_ID"));
	
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","List",{"tree_parent_ID"},{FieldsValues}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserUi::Read () {

	string Id=HTTP.GetHttpParam("id");

	AddJsVarFile("XaModel","XaUser");
	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("RowId",Id);
	
	/* data */

	vector <string> FieldsValues ={};
	FieldsValues.push_back(Id);

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","Read",{"id"},{FieldsValues}));
	CheckResponse(CallResponse);
	
	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiRead");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);

};

void XaUserUi::CreateFrm() {

	AddJsVarFile("XaModel","XaUser");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiCreateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserUi::Create() {

	auto Fields=CreatePrepare({"XaUser"},"/XaUser/fieldset/field","XaUser");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaUserUi::UpdateFrm() {

	AddJsVarFile("XaModel","XaUser");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	vector <string> FieldsValues ={};
	FieldsValues.push_back(HTTP.GetHttpParam("id"));

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","ReadForUpdateFrm",{"id"},{FieldsValues}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiUpdateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserUi::Update() {

	auto Fields=UpdatePrepare({"XaUser"},"/XaUser/fieldset/field","XaUser");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","Update",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaUserUi::Delete() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","Delete",{"id"},{HTTP.GetHttpParam("id")}));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

XaUserUi::~XaUserUi(){
};