#include <XaUserAddressMailTypeUi.h>
#include <XaLibAction.h>

XaUserAddressMailTypeUi::XaUserAddressMailTypeUi(){
};

void XaUserAddressMailTypeUi::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressMailTypeUi::CreateFrm() {

    AddJsVarFile("XaModel","XaUserAddressMailType");
    AddJsVarString("XaGuiStyle","default");

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressMailTypeUi::Create() {

    auto Fields=CreatePrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field","XaUserAddressMailType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressMailType","Create",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressMailTypeUi::ListAsOptions() {

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressMailType","ListAsOptions",{"order_by"},{"name"}));
    CheckResponse(CallResponse);

    RESPONSE.Content=CallResponse;
};

void XaUserAddressMailTypeUi::UpdateFrm() {

    AddJsVarFile("XaModel","XaUserAddressMailType");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressMailType","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressMailTypeUi::Update() {

    auto Fields=UpdatePrepare({"XaUserAddressMailType"},"/XaUserAddressMailType/fieldset/field","XaUserAddressMailType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressMailType","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressMailTypeUi::Delete() {

    string Id=HTTP.GetHttpParam("id");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressMailType","Delete",{"id"},{Id}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaUserAddressMailTypeUi::~XaUserAddressMailTypeUi(){
};