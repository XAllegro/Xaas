#include <XaUserAddressGeoTypeUi.h>
#include <XaLibAction.h>

XaUserAddressGeoTypeUi::XaUserAddressGeoTypeUi(){
};

void XaUserAddressGeoTypeUi::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressGeoTypeUi::CreateFrm() {

    AddJsVarFile("XaModel","XaUserAddressGeoType");
    AddJsVarString("XaGuiStyle","default");

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressGeoTypeUi::Create() {

    auto Fields=CreatePrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field","XaUserAddressGeoType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressGeoType","Create",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressGeoTypeUi::ListAsOptions() {

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressGeoType","ListAsOptions",{"order_by"},{"name"}));
    CheckResponse(CallResponse);

    RESPONSE.Content=CallResponse;
};

void XaUserAddressGeoTypeUi::UpdateFrm() {

    AddJsVarFile("XaModel","XaUserAddressGeoType");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressGeoType","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaUserAddressGeoTypeUi::Update() {

    auto Fields=UpdatePrepare({"XaUserAddressGeoType"},"/XaUserAddressGeoType/fieldset/field","XaUserAddressGeoType");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressGeoType","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaUserAddressGeoTypeUi::Delete() {

    string Id=HTTP.GetHttpParam("id");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUserAddressGeoType","Delete",{"id"},{Id}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaUserAddressGeoTypeUi::~XaUserAddressGeoTypeUi(){
};