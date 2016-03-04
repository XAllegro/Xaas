#include <XaDomainUi.h>
#include <XaLibAction.h>

XaDomainUi::XaDomainUi(){
};

void XaDomainUi::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="CreateFrm") {
	this->CreateFrm();
    } else if (CalledEvent=="Create") {
        this->Create();
    } else if (CalledEvent=="List") {
        this->List();
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

void XaDomainUi::CreateFrm() {

    AddJsVarFile("XaModel","XaDomain");
    AddJsVarString("XaGuiStyle","default");

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaDomainUi::Create() {

    auto Fields=CreatePrepare({"XaDomain"},"/XaDomain/fieldset/field","XaDomain");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","Create",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaDomainUi::List () {

    AddJsVarFile("XaModel","XaDomain");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","List",{""},{""}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiList");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaDomainUi::ListAsOptions() {

    string Domain = HTTP.GetHttpParam("domain");
    string TreeParentId=HTTP.GetHttpParam("tree_parent_ID");
    
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","ListAsOptions",{"order_by","domain","tree_parent_ID"},{"name",Domain,TreeParentId}));
    CheckResponse(CallResponse);

    RESPONSE.Content=CallResponse;
};

void XaDomainUi::UpdateFrm() {

    AddJsVarFile("XaModel","XaDomain");
    AddJsVarString("XaGuiStyle","default");

    /* data */

    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);

    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaDomainUi::Update() {

    auto Fields=UpdatePrepare({"XaDomain"},"/XaDomain/fieldset/field","XaDomain");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

void XaDomainUi::Delete() {

    string Id=HTTP.GetHttpParam("id");
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaDomain","Delete",{"id"},{Id}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaDomainUi::~XaDomainUi(){
};