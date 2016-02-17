#include <XaUserAddressPhoneCodeUi.h>
#include <XaLibAction.h>

XaUserAddressPhoneCodeUi::XaUserAddressPhoneCodeUi(){
};

void XaUserAddressPhoneCodeUi::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="CreateFrm") {
	this->CreateFrm();
    } else if (CalledEvent=="Create") {
        this->Create();
    } else if (CalledEvent=="ListAsOptions") {
        this->ListAsOptions();
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

void XaUserAddressPhoneCodeUi::CreateFrm() {

    AddJsVarFile("XaModel","XaUserAddressPhoneCode");
    AddJsVarString("XaGuiStyle","default");

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressPhoneCodeUi::Create() {

    auto Fields=CreatePrepare({"XaUserAddressPhoneCode"},"/XaUserAddressPhoneCode/fieldset/field","XaUserAddressPhoneCode");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneCode","Create",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressPhoneCodeUi::ListAsOptions() {

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneCode","ListAsOptions",{"order_by"},{"name"}));
    CheckResponse(CallResponse);

    RESPONSE.Content=CallResponse;
};

void XaUserAddressPhoneCodeUi::UpdateFrm() {

    AddJsVarFile("XaModel","XaUserAddressPhoneCode");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneCode","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressPhoneCodeUi::Update() {

    auto Fields=UpdatePrepare({"XaUserAddressPhoneCode"},"/XaUserAddressPhoneCode/fieldset/field","XaUserAddressPhoneCode");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneCode","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressPhoneCodeUi::Delete() {

    string Id=HTTP.GetHttpParam("id");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneCode","Delete",{"id"},{Id}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaUserAddressPhoneCodeUi::~XaUserAddressPhoneCodeUi(){
};