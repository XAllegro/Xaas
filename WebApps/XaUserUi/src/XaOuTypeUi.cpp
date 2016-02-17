#include <XaOuTypeUi.h>
#include <XaLibAction.h>

XaOuTypeUi::XaOuTypeUi(){
};

void XaOuTypeUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="CreateFrm") {
		this->CreateFrm();
    } else if (CalledEvent=="Create") {
		this->Create();
    } else if (CalledEvent=="List") {
		this->List();
    } else if (CalledEvent=="ListAsOptions") {
		this->ListAsOptions();
    }  else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOuTypeUi::CreateFrm() {

	AddJsVarFile("XaModel","XaOuType");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiCreateFrm");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaOuTypeUi::Create() {

	auto Fields=CreatePrepare({"XaOuType"},"/XaOuType/fieldset/field","XaOuType");
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";
};

void XaOuTypeUi::List() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","List",{},{}));
	CheckResponse(CallResponse);

	AddJsVarString("XaGuiStyle","default");
	AddJsVarString("WsData",CallResponse);

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles({"XaGuiHead","XaGuiHeader","XaGuiListRaw"}),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaOuTypeUi::ListAsOptions() {

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","ListAsOptions",{},{}));
	CheckResponse(CallResponse);

	RESPONSE.Content=CallResponse;
};

XaOuTypeUi::~XaOuTypeUi() {
};