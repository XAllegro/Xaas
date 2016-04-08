#include <XaMediaDataUi.h>

XaMediaDataUi::XaMediaDataUi(){
};

void XaMediaDataUi::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="List") {
        this->List();
    }else if (CalledEvent=="Read") {
        this->Read();
    }else if (CalledEvent=="CreateFrm") {
        this->CreateFrm();
    }else if (CalledEvent=="Create"){
        this->Create();
    }else if (CalledEvent=="Update"){
        this->Update();
    }else if (CalledEvent=="UpdateFrm"){
        this->UpdateFrm();
    }else if (CalledEvent=="Delete"){
        this->Delete();
    }else {
        LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"REQUESTed Event Does Not Exists 2-> "+CalledEvent);
    }

};

void XaMediaDataUi::List() {

	string XaMedia_ID=HTTP.GetHttpParam("XaMedia_ID");

	AddJsVarString("XaMedia_ID",XaMedia_ID);
	AddJsVarFile("XaModel","XaMediaData");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","List",{"XaMedia_ID"},{XaMedia_ID}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaMediaDataList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaDataUi::Read() {

	string Id=HTTP.GetHttpParam("id");

	AddJsVarString("RowId",Id);
	AddJsVarFile("XaModel","XaMediaData");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","Read",{"id"},{Id}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiRead");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaDataUi::CreateFrm() {

	string XaMedia_ID=HTTP.GetHttpParam("XaMedia_ID");

	AddJsVarString("XaMedia_ID",XaMedia_ID);
    AddJsVarFile("XaModel","XaMediaData");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaMediaDataCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaDataUi::Create (){

    auto Fields=CreatePrepare({"XaMediaData"},"/XaMediaData/fieldset/field","XaMediaData");
	
	get<0>(Fields).push_back("XaMediaData-XaMedia_ID");
	get<1>(Fields).push_back(HTTP.GetHttpParam("XaMediaData-XaMedia_ID"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";

};

void XaMediaDataUi::Update (){
    
    XaLibCurl LibCurl;
    
    auto Fields=UpdatePrepare({"XaMediaData"},"/XaMediaData/fieldset/field","XaMediaData");
    
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";

};

void XaMediaDataUi::UpdateFrm() {

    AddJsVarFile("XaMediaData","XaMediaData");
    AddJsVarString("XaGuiStyle","default");

    /* data */
    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);
    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};


void XaMediaDataUi::Delete (){
    
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMediaData","Delete",{"id"},{HTTP.GetHttpParam("id")}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaMediaDataUi::~XaMediaDataUi(){
};