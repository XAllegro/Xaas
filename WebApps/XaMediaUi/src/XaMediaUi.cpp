#include <XaMediaUi.h>

XaMediaUi::XaMediaUi(){
};

void XaMediaUi::Dispatcher (const string &CalledEvent) {

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

void XaMediaUi::List() {

	string XaField_ID=HTTP.GetHttpParam("XaField_ID");
        string XaTable=HTTP.GetHttpParam("XaTable");

	AddJsVarString("XaField_ID",XaField_ID);
        AddJsVarString("XaTable",XaTable);
	AddJsVarFile("XaModel","XaMedia");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","List",{"XaField_ID","XaTable"},{XaField_ID,XaTable}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaMediaList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaUi::Read() {

	string Id=HTTP.GetHttpParam("id");

	AddJsVarString("RowId",Id);
	AddJsVarFile("XaModel","XaMedia");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","Read",{"id"},{Id}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiRead");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaUi::CreateFrm() {

	string XaField_ID=HTTP.GetHttpParam("XaField_ID");
        string XaTable=HTTP.GetHttpParam("XaTable");

	AddJsVarString("XaField_ID",XaField_ID);
        AddJsVarString("XaTable",XaTable);
    AddJsVarFile("XaModel","XaMedia");
	AddJsVarString("XaGuiStyle","default");

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaMediaCreateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

void XaMediaUi::Create (){

    auto Fields=CreatePrepare({"XaMedia"},"/XaMedia/fieldset/field","XaMedia");
	
	get<0>(Fields).push_back("XaMedia-XaField_ID");
	get<1>(Fields).push_back(HTTP.GetHttpParam("XaMedia-XaField_ID"));
        
        get<0>(Fields).push_back("XaMedia-XaTable");
	get<1>(Fields).push_back(HTTP.GetHttpParam("XaMedia-XaTable"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","Create",get<0>(Fields),get<1>(Fields)));
	CheckResponse(CallResponse);
	RESPONSE.Content="OK";

};

void XaMediaUi::Update (){
    
    XaLibCurl LibCurl;
    
    auto Fields=UpdatePrepare({"XaMedia"},"/XaMedia/fieldset/field","XaMedia");
    
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","Update",get<0>(Fields),get<1>(Fields)));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";

};

void XaMediaUi::UpdateFrm() {

    AddJsVarFile("XaMedia","XaMedia");
    AddJsVarString("XaGuiStyle","default");

    /* data */
    vector <string> FieldsValues ={};
    FieldsValues.push_back(HTTP.GetHttpParam("id"));

    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","ReadForUpdateFrm",{"id"},{FieldsValues}));
    CheckResponse(CallResponse);

    AddJsVarString("XaData",CallResponse);
    /* end of data */

    vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
    Templates.push_back("XaGuiUpdateFrm");

    RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};


void XaMediaUi::Delete (){
    
    XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaMedia","Delete",{"id"},{HTTP.GetHttpParam("id")}));
    CheckResponse(CallResponse);
    RESPONSE.Content="OK";
};

XaMediaUi::~XaMediaUi(){
};