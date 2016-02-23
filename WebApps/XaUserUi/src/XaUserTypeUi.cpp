#include <XaUserTypeUi.h>
#include <XaLibAction.h>

XaUserTypeUi::XaUserTypeUi(){
};

void XaUserTypeUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {
		this->CreateFrm();
    } else if (CalledEvent=="Create") {
        this->Create();
    } else if (CalledEvent=="List") {
        this->List();
    } else if (CalledEvent=="Read") {
        this->Read();
    } else if (CalledEvent=="UpdateFrm") {
        this->UpdateFrm();
    } else if (CalledEvent=="Update") {
        this->Update();
    } else if (CalledEvent=="Delete") {
        this->Delete();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42:: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserTypeUi::CreateFrm() {

	AddJsVarFile("XaModel","XaUserType");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiCreateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserTypeUi::Create() {

	auto Fields=CreatePrepare({"XaUserType"},"/XaUserType/fieldset/field","XaUserType");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaUserTypeUi::List () {

	AddJsVarFile("XaModel","XaUserType");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","List",{},{}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserTypeUi::Read() {

	string Id=HTTP.GetHttpParam("id");

	AddJsVarFile("XaModel","XaUserType");
	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("RowId",Id);
	
	/* data */

	vector <string> FieldsValues ={};
	FieldsValues.push_back(Id);

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","Read",{"id"},{FieldsValues}));
	CheckResponse(CallResponse);
	
	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiRead");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserTypeUi::UpdateFrm() {

	AddJsVarFile("XaModel","XaUserType");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	vector <string> FieldsValues ={};
	FieldsValues.push_back(HTTP.GetHttpParam("id"));

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","ReadForUpdateFrm",{"id"},{FieldsValues}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiUpdateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserTypeUi::Update() {

	auto Fields=UpdatePrepare({"XaUserType"},"/XaUserType/fieldset/field","XaUserType");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","Update",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaUserTypeUi::Delete() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserType","Delete",{"id"},{HTTP.GetHttpParam("id")}));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

XaUserTypeUi::~XaUserTypeUi() {
};