#include <XaLibAction.h>

XaLibAction::XaLibAction(){
};

vector<string> XaLibAction::AddHtmlFiles(const vector<string>& FileName){

	vector<string> HtmlFiles;

	for (auto &i : FileName) {

		//BUILDING THE PATH
		string HtmlDefaultPath=SETTINGS["HtmlDir"]+i+".html";
		string HtmlSharedPath=SETTINGS["SharedDir"]+"html/"+i+".html";

		//TEST THE FILE
		unique_ptr<FILE, int(*)(FILE*)> f1(fopen(HtmlDefaultPath.c_str(), "r"), fclose);
		unique_ptr<FILE, int(*)(FILE*)> f2(fopen(HtmlSharedPath.c_str(), "r"), fclose);

		//ADD THE FILE TO THE VECTOR
		if (f1) {
			HtmlFiles.push_back(HtmlDefaultPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added HtmlFile Custom-> "+HtmlDefaultPath);

		} else if (f2) {
			HtmlFiles.push_back(HtmlSharedPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added HtmlFile Shared-> "+HtmlSharedPath);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Html File Does Not Exist -> "+i);
			throw 204;
		}
	}	

	return HtmlFiles;
};

void XaLibAction::AddHtmlFile(const string& FilePath){

	string HtmlDefaultPath=SETTINGS["HtmlDir"]+FilePath+".html";
	string HtmlSharedPath=SETTINGS["SharedDir"]+"html/"+FilePath+".html";

	unique_ptr<FILE, int(*)(FILE*)> f1(fopen(HtmlDefaultPath.c_str(), "r"), fclose);
	unique_ptr<FILE, int(*)(FILE*)> f2(fopen(HtmlSharedPath.c_str(), "r"), fclose);

	if (f1) {
		HtmlFiles.push_back(HtmlDefaultPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added HtmlFile Custom-> "+HtmlDefaultPath);

	} else if (f2) {
		HtmlFiles.push_back(HtmlSharedPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added HtmlFile Shared-> "+HtmlSharedPath);

	} else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Html File Does Not Exist-> "+FilePath);
	}
};

void XaLibAction::AddHtmlString(const string& HtmlString){

	//ToDo= Check if is valid Xml String
	HtmlStrings.push_back(HtmlString);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlString -> "+HtmlString);
};

void XaLibAction::AddJsVarFile(const string& VarName, const string& FileName){

	string DefaultPath=SETTINGS["XmlDir"]+FileName+".xml";
	string SharedPath=SETTINGS["SharedDir"]+"xml/"+FileName+".xml";

	unique_ptr<FILE, int(*)(FILE*)> f1(fopen(DefaultPath.c_str(), "r"), fclose);
	unique_ptr<FILE, int(*)(FILE*)> f2(fopen(SharedPath.c_str(), "r"), fclose);

	if (f1) {
		JsVarFiles.push_back(VarName);
		JsVarFiles.push_back(DefaultPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Js Value From File Custom-> "+DefaultPath);

	} else if (f2) {
		JsVarFiles.push_back(VarName);
		JsVarFiles.push_back(SharedPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Js Value From File Shared-> "+SharedPath);

	} else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested  File Does Not Exist-> "+FileName);
	}
};

void XaLibAction::AddJsVarString(const string& VarName, const string& VarString){

	JsVarStrings.push_back(VarName);
	JsVarStrings.push_back(VarString);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added JsString -> "+VarString);
};

void XaLibAction::AddXmlFile(const string& FilePath){

	string XmlDefaultPath=SETTINGS["XmlDir"]+FilePath+".xml";
	string XmlSharedPath=SETTINGS["SharedDir"]+"xml/"+FilePath+".xml";

	unique_ptr<FILE, int(*)(FILE*)> f1(fopen(XmlDefaultPath.c_str(), "r"), fclose);
	unique_ptr<FILE, int(*)(FILE*)> f2(fopen(XmlSharedPath.c_str(), "r"), fclose);

	if (f1) {
		XmlFiles.push_back(XmlDefaultPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Custom-> "+XmlDefaultPath);

	} else if (f2) {
		XmlFiles.push_back(XmlSharedPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Shared-> "+XmlSharedPath);

	} else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Xml File Does Not Exist-> "+FilePath);
	}
};

vector<string> XaLibAction::AddXmlFile(const vector<string>& FileName){

	vector<string> XmlFiles;

	for (auto &i : FileName) {

		//BUILDING THE PATH
		string XmlDefaultPath=SETTINGS["XmlDir"]+i+".xml";
		string XmlSharedPath=SETTINGS["SharedDir"]+"xml/"+i+".xml";

		//TEST THE FILE
		unique_ptr<FILE, int(*)(FILE*)> f1(fopen(XmlDefaultPath.c_str(), "r"), fclose);
		unique_ptr<FILE, int(*)(FILE*)> f2(fopen(XmlSharedPath.c_str(), "r"), fclose);

		//ADD THE FILE TO THE VECTOR
		if (f1) {
			XmlFiles.push_back(XmlDefaultPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Custom-> "+XmlDefaultPath);

		} else if (f2) {
			XmlFiles.push_back(XmlSharedPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Shared-> "+XmlSharedPath);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Xml File Does Not Exist -> "+i);
			throw 203;
		}
	}	

	return XmlFiles;
};

void XaLibAction::AddXmlString(const string& XmlString){

	//ToDo= Check if is valid Xml String
	XmlStrings.push_back(XmlString);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlString -> "+XmlString);
};

void XaLibAction::AddXslFile(const string& FilePath){

	string XslDefaultPath=SETTINGS["XslDir"]+FilePath+".xsl";
	string XslSharedPath=SETTINGS["SharedDir"]+"xsl/"+FilePath+".xsl";

	unique_ptr<FILE, int(*)(FILE*)> f1(fopen(XslDefaultPath.c_str(), "r"), fclose);
	unique_ptr<FILE, int(*)(FILE*)> f2(fopen(XslSharedPath.c_str(), "r"), fclose);

	if (f1) {
		XslFiles.push_back(XslDefaultPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XslFile Custom-> "+XslDefaultPath);

	} else if (f2) {
		XslFiles.push_back(XslSharedPath);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XslFile Shared-> "+XslSharedPath);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Xsl File Does Not Exist-> "+FilePath);
	}
};

void XaLibAction::AddXslString(const string& XslString){

	XslStrings.push_back(XslString);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XslString -> "+XslString);
};

void XaLibAction::AddXslParamCommon() {

	XslParams.push_back("AppName");
	XslParams.push_back(SETTINGS["AppName"]);
	XslParams.push_back("GuiStyle");
	XslParams.push_back(SETTINGS["GuiStyle"]);
	XslParams.push_back("token");
	XslParams.push_back(SESSION.Token);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XslParamCommon -> AppName::"+SETTINGS["AppName"]+" GuiStyle::"+SETTINGS["GuiStyle"]);
};

void XaLibAction::AddXslParam(const string& ParamName, const string& ParamValue) {

	XslParams.push_back(ParamName);
	XslParams.push_back(ParamValue);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XslParam -> "+ParamName+"::"+ParamValue);
};

vector <string> XaLibAction::SetPageLayout (const string &LayoutType) {

	vector<string> HtmlFiels={};
	
	if (LayoutType=="complete" || LayoutType=="NoHttpParam"){

		HtmlFiels={"XaGuiHead","XaGuiHeader"};

	} else if (LayoutType=="include") {
		
		HtmlFiels={"XaGuiHeadVoid"};
	
	} else if (LayoutType=="modal") {

		HtmlFiels={"XaGuiHead"};
	}

	return HtmlFiels;
};
		
void XaLibAction::SetLayout(const string &LayoutType){

	if (LayoutType=="Standalone" ) {

		AddXslFile("XaGuiHead");
		AddXslFile("XaGuiHeader");
		AddXslFile("XaGuiFooter");
		AddXslFile("XaGuiNav");
		AddXslFile("templates");

		//AddXslFile("manifest");
		AddXmlFile("XaLabel-"+REQUEST.Language);
		AddXmlFile("XaGuiNav");

	} else if (LayoutType=="Included") {

		AddXslFile("templates");

	} else if (LayoutType=="Standard" || LayoutType=="NoHttpParam") {

		AddXslFile("XaGuiHead");
		AddXslFile("XaGuiHeader");
		AddXslFile("XaGuiFooter");
		AddXslFile("XaGuiNav");
		AddXslFile("templates");

		AddXmlFile("XaLabel-"+REQUEST.Language);
		AddXmlFile("XaGuiNav");

	} else if (LayoutType=="InfoPage") {

		AddXslFile("XaGuiHead");
		AddXslFile("XaInfoPage");
		AddXmlFile("XaInfoPage");

	} else if (LayoutType=="Chart") {

		AddXslFile("templates");
		AddXmlFile("XaLabel-"+REQUEST.Language);

	} else if (LayoutType=="ModalWindow") {

		AddXslFile("XaGuiHead");
		AddXslFile("templates");
		AddXmlFile("XaLabel-"+REQUEST.Language);

	} else if (LayoutType=="LoginFrm") {

		AddXslFile("XaGuiHead");
		AddXslFile("XaGuiHeaderInternet");
		AddXslFile("XaGuiFooter");
		AddXmlFile("XaLabel-"+REQUEST.Language);

	} else if (LayoutType=="Search") {

		AddXslFile("XaGuiHead");
		AddXslFile("XaGuiHeader");
		AddXslFile("XaGuiFooter");
		AddXslFile("XaGuiNav");
		AddXslFile("templates-search");
		AddXmlFile("XaLabel-"+REQUEST.Language);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Layout does not exists -> "+LayoutType);
	}

    LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Layout -> "+LayoutType);

};

tuple<vector<string>,vector<string>> XaLibAction::CreatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,const string& ModelName) {

	//TODO:GESTIONE ERRORI

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	tuple<vector<string>,vector<string>> Fields;

	for (auto i=0;i<FieldsNum;i++) {
		//LOADING PROPERTIES

		string FieldName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
		string FieldValue=HTTP.GetHttpParam(ModelName+"-"+FieldName);

		get<0>(Fields).push_back(FieldName);
		get<1>(Fields).push_back(FieldValue);

		//FieldsName.push_back(FieldName);
		//FieldsValue.push_back(FieldValue);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +FieldName +" :: " + FieldValue);			
	};
	
	return Fields;

};

tuple<vector<string>,vector<string>> XaLibAction::UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,const string& ModelName) {

	//TODO:GESTIONE ERRORI

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	tuple<vector<string>,vector<string>> Fields;

	for (auto i=0;i<FieldsNum;i++) {
		//LOADING PROPERTIES

		/* Only updateble fields */
		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update")=="yes") {
			string FieldName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
			string FieldValue=HTTP.GetHttpParam(ModelName+"-"+FieldName);

			get<0>(Fields).push_back(FieldName);
			get<1>(Fields).push_back(FieldValue);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +FieldName +" :: " + FieldValue);
		}
	};

	// ADD id To FIELD LIST

	string FieldName="id";
	string FieldValue=HTTP.GetHttpParam(ModelName+"-"+FieldName);
	get<0>(Fields).push_back(FieldName);
	get<1>(Fields).push_back(FieldValue);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +FieldName +" :: " + FieldValue);

	return Fields;

};

string XaLibAction::BuildBackEndCall(const string& Object, const string& Event,const vector <string>& ParamName,const vector <string>& ParamValue){

	string Call=BuildBackEndCallBase();

	Call.append("&");
	Call.append("Data=");
	
	string WsData={};
	
	WsData.append("<WsData>");
	
	//ADDING TOKEN
	WsData.append("<login><token>");
	WsData.append(SESSION.Token);
	WsData.append("</token><client_ip>");
	WsData.append(SESSION.ClientIp);
	WsData.append("</client_ip></login>");
	
	//ADDING OPERATION
	WsData.append(BuildBackEndCallSectionOperation(Object,Event));
	
	//ADDING PARAMS
	WsData.append(BuildBackEndCallSectionParams(ParamName,ParamValue));

	WsData.append("</WsData>");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);

	if (SETTINGS["WsDefaultEncoding"]=="no"){

		XaLibChar LibChar;
		return Call+LibChar.UrlEncode(WsData);

	} else if (SETTINGS["WsDefaultEncoding"]=="B64") {

		return Call+WsData;

	} else {
		
		return Call+WsData;
	
	}
};

string XaLibAction::BuildBackEndCallLogin(const string& Username, const string& Password){

	string Call=BuildBackEndCallBase();

	Call.append("&");
	Call.append("Data=");

	//FARE IL CASO CRITTOGRAFATO ED ENCODATO

	string SectionLogin="<WsData><login><username>"+Username+"</username><password>"+Password+"</password></login><operation><object>XaUserLogin</object><event>Login</event></operation></WsData>";
	Call.append(SectionLogin);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);
	return Call;

};

string XaLibAction::BuildBackEndCallBase(){

	if (SETTINGS["WsDefaultReqType"] =="xml") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call Type -> "+SETTINGS["WsDefaultReqType"]);

		string Call="";
		Call.append(SETTINGS["WsDefaultBackEndUrl"]);

		Call.append("?");
		Call.append("ReqType=");
		Call.append(SETTINGS["WsDefaultReqType"]);

		Call.append("&");
		Call.append("Encoding=");
		Call.append(SETTINGS["WsDefaultEncoding"]);

		Call.append("&");
		Call.append("Encryption=");
		Call.append(SETTINGS["WsDefaultEncryption"]);

		Call.append("&");
		Call.append("ResType=");
		Call.append(SETTINGS["WsDefaultResType"]);

		Call.append("&");
		Call.append("ConsumerId=");
		Call.append(SETTINGS["WsConsumerId"]);

		//Call.append("&");
		//Call.append("WsData=");

		
		//FARE IL CASO CRITTOGRAFATO ED ENCODATO

		//&Data=<WsData><login><username>alex@xallegro.com</username><password>ranokkio</password></login><operation><object>XaUser</object><event>Login</event></operation></WsData>

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);
		return Call;

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call Type Is Not Supported ->"+SETTINGS["WsDefaultReqType"]);
		throw 201;
	}
};

string XaLibAction::BuildBackEndCallSectionParams(const vector <string>& ParamName,const vector <string>& ParamValue){

	string ParamSection="<params>";
	
	if (ParamName.size()!=ParamValue.size()) {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Parameters and Values Have Different Size");
		throw 202;
	
	} else if(ParamName.size()==0){
		
		ParamSection.append("<p><n></n><v></v></p>");

	} else {
		
		for (auto i=0; i<ParamName.size(); i++) {

			ParamSection.append("<p><n>");

			ParamSection.append(ParamName[i]);
			ParamSection.append("</n><v>");

			ParamSection.append(ParamValue[i]);
			ParamSection.append("</v></p>");
		}
	}

	ParamSection.append("</params>");

	return ParamSection;
};

string XaLibAction::BuildBackEndCallSectionOperation(const string& Object, const string& Event){

	string SectionOperation="<operation><object>"+Object+"</object><event>"+Event+"</event></operation>";
	return SectionOperation;
};

void XaLibAction::CheckResponse(const string& Response) {

	xmlDocPtr XmlResponse=XaLibDom::DomFromString(Response);
	string Error=XaLibDom::GetElementValueByXPath(XmlResponse,"//error/number");

	if (Error!="ELEMENT-NOT-DEFINED") {

		string Description=XaLibDom::GetElementValueByXPath(XmlResponse,"//error/description");

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"BackEnd Returned An Error-> Number "+Error+" :: Description "+Description);

		throw FromStringToInt(Error);
	}
};

void XaLibAction::Execute(){

	//EXECUTE OBJECT DISPATCHER (CLASS DISPATCHER)
	if (REQUEST.CalledObject!="" && REQUEST.CalledEvent!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Object Event ->"+REQUEST.CalledEvent);
		this->Dispatcher(REQUEST.CalledEvent);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Event Is empty");
		throw 621;
	}
};

void XaLibAction::Dispatcher (const string &CalledEvent){};

XaLibAction::~XaLibAction(){
};