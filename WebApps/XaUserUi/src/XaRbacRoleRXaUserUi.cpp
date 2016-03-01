#include <XaRbacRoleRXaUserUi.h>
#include <XaLibAction.h>

XaRbacRoleRXaUserUi::XaRbacRoleRXaUserUi(){
};

void XaRbacRoleRXaUserUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {
		this->CreateFrm();
    } else if (CalledEvent=="Create") {
        this->Create();
    } else if (CalledEvent=="List") {
        this->List();
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

void XaRbacRoleRXaUserUi::CreateFrm() {

	AddJsVarFile("XaModel","XaRbacRoleRXaUser");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaRbacRoleRXaUserCreateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaRbacRoleRXaUserUi::Create() {

	auto Fields=CreatePrepare({"XaRbacRoleRXaUser"},"/XaRbacRoleRXaUser/fieldset/field","XaRbacRoleRXaUser");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaRbacRoleRXaUser","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaRbacRoleRXaUserUi::List () {

	AddJsVarFile("XaModel","XaRbacRoleRXaUser");
	AddJsVarString("XaGuiStyle","default");

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaRbacRoleRXaUser","List",{"XaUser_ID"},{XaUser_ID}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaRbacRoleRXaUserUi::UpdateFrm() {

	AddJsVarFile("XaModel","XaRbacRoleRXaUser");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	vector <string> FieldsValues ={};
	FieldsValues.push_back(HTTP.GetHttpParam("id"));

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaRbacRoleRXaUser","ReadForUpdateFrm",{"id"},{FieldsValues}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaRbacRoleRXaUserUpdateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaRbacRoleRXaUserUi::Update() {

	auto Fields=UpdatePrepare({"XaRbacRoleRXaUser"},"/XaRbacRoleRXaUser/fieldset/field","XaRbacRoleRXaUser");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaRbacRoleRXaUser","Update",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaRbacRoleRXaUserUi::Delete() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaRbacRoleRXaUser","Delete",{"id"},{HTTP.GetHttpParam("id")}));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

XaRbacRoleRXaUserUi::~XaRbacRoleRXaUserUi() {
};