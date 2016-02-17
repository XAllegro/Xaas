#include <XaUserAddressPhoneTypeUi.h>
#include <XaLibAction.h>

XaUserAddressPhoneTypeUi::XaUserAddressPhoneTypeUi(){
};

void XaUserAddressPhoneTypeUi::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressPhoneTypeUi::CreateFrm() {

    AddJsVarFile("XaModel","XaUserAddressPhoneType");
    AddJsVarString("XaGuiStyle","default");

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressPhoneTypeUi::Create() {

    auto Fields=CreatePrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field","XaUserAddressPhoneType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneType","Create",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressPhoneTypeUi::ListAsOptions() {

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneType","ListAsOptions",{"order_by"},{"name"}));
    CheckResponse(CallResponse);

    RESPONSE.Content=CallResponse;
};

void XaUserAddressPhoneTypeUi::UpdateFrm() {

    AddJsVarFile("XaModel","XaUserAddressPhoneType");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneType","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressPhoneTypeUi::Update() {

    auto Fields=UpdatePrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field","XaUserAddressPhoneType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneType","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressPhoneTypeUi::Delete() {

    string Id=HTTP.GetHttpParam("id");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressPhoneType","Delete",{"id"},{Id}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaUserAddressPhoneTypeUi::~XaUserAddressPhoneTypeUi(){
};