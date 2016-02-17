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

		string FieldName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
		string FieldValue=HTTP.GetHttpParam(ModelName+"-"+FieldName);

		get<0>(Fields).push_back(FieldName);
		get<1>(Fields).push_back(FieldValue);

		//FieldsName.push_back(FieldName);
		//FieldsValue.push_back(FieldValue);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +FieldName +" :: " + FieldValue);
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

/*
string XaLibAction::BuildBackEndCallSectionParams(const vector<string>& Names, const vector<string>& Values){
};
*/

/*
void XaLibAction::GetResponse(){

	//EXECUTE OBJECT DISPATCHER (CLASS DISPATCHER)
	if (REQUEST.CalledObject!="" && REQUEST.CalledEvent!="") {

		string Event=REQUEST.CalledEvent;
		//this->ResetRequest();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Object Event ->"+Event);
		this->Dispatcher(Event);

	} else {

	}
};*/
/*
void XaLibAction::ErrorPage (const string& ErrorType) {

	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Redirection to ErrorPage -> "+ErrorType);

	RESPONSE.Object="XaPages";
	RESPONSE.Event="XaInfoPage";
	RESPONSE.Headers="&ErrorMessage="+ErrorType;
};

void XaLibAction::ErrorExit (const string& ErrorType) {

	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Redirection to ErrorPage -> "+ErrorType);

	REQUEST.CalledObject="XaPages";
	REQUEST.CalledEvent="XaInfoPage";
	REQUEST.HeadersStringCustom="&ErrorMessage="+ErrorType;
};

void XaLibAction::AddOptionsByDb(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr){

	OptionReturnedFields.push_back("id");
	OptionReturnedFields.push_back("name");
	
	OptionWhereFields.push_back("active");
	OptionWhereFields.push_back("deleted");

	OptionWhereValues.push_back("1");
	OptionWhereValues.push_back("0");

	OptionOrderByFields.push_back("name");

	DbResMap DbRes;

	unique_ptr<XaLibSql> LibSql (new XaLibSql());

	DbRes=LibSql->Select(DB_READ,TableName,OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["id"];
		string OptionLabel=DbRes[n]["name"];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Db-> "+ TableName + " - " + XPathExpr);
};

void XaLibAction::AddOptionsByDb(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr,string OptionValueField,string OptionLabelField){

	OptionReturnedFields.push_back(OptionValueField);
	OptionReturnedFields.push_back(OptionLabelField);
	
	OptionWhereFields.push_back("active");
	OptionWhereFields.push_back("deleted");

	OptionWhereValues.push_back("1");
	OptionWhereValues.push_back("0");

	DbResMap DbRes;
	XaLibSql* LibSql=new XaLibSql();
	DbRes=LibSql->Select(DB_READ,TableName,OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);

	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n][OptionValueField];
		string OptionLabel=DbRes[n][OptionLabelField];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Db-> "+ TableName + " - " + XPathExpr);
};

void XaLibAction::AddOptionsByDbWithCondition(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr,string Condition){

	DbResMap DbRes;

	XaLibSql* LibSql=new XaLibSql();

	string Qry="SELECT id,name FROM "+TableName+" WHERE active=1 AND deleted=0 "+Condition+ " ORDER BY name";
	
	DbRes=LibSql->FreeQuery(DB_READ,Qry);

	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["id"];
		string OptionLabel=DbRes[n]["name"];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Db-> "+ TableName + " - " + XPathExpr);
};

void XaLibAction::AddOptionsByDomain(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string XPathExpr){

	OptionReturnedFields.push_back("id");
	OptionReturnedFields.push_back("name");

	OptionWhereFields.push_back("active");
	OptionWhereFields.push_back("deleted");
	OptionWhereFields.push_back("domain");

	OptionWhereValues.push_back("1");
	OptionWhereValues.push_back("0");
	OptionWhereValues.push_back(XaDomain);

	OptionOrderByFields.push_back("description");

	DbResMap DbRes;

	XaLibSql* LibSql=new XaLibSql();
	DbRes=LibSql->Select(DB_READ,"XaDomain",OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);
	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["id"];
		string OptionLabel=DbRes[n]["name"];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Domain-> "+ XaDomain + " - " + XPathExpr);
};


void XaLibAction::AddOptionsByDomainAndUser(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string StrUserId, string XPathExpr){

	DbResMap DbRes;

	//ADD OPTIONS VALUE
	XaLibSql* LibSql=new XaLibSql();

	string QryDomainItems="SELECT XaDomain.id, XaDomain.name from XaDomain, XaUser, XaUserXaDomain WHERE XaDomain.domain='"+XaDomain+"' AND XaUser.id="+StrUserId+" AND XaUserXaDomain.XaUser_ID=XaUser.id AND XaUserXaDomain.XaDomain_ID=XaDomain.id";
	QryDomainItems+=" AND XaDomain.active=1 AND XaDomain.deleted=0 AND XaUser.active=1 AND XaUser.deleted=0 AND XaUserXaDomain.active=1 AND XaUserXaDomain.deleted=0";
	QryDomainItems+=" ORDER BY XaDomain.name";
	
	DbRes=LibSql->FreeQuery(DB_READ,QryDomainItems);

	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["id"];
		string OptionLabel=DbRes[n]["name"];

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Domain-> "+ XaDomain + " - " + XPathExpr);
};


void XaLibAction::AddOptionsByDomainWithDescription(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XaDomain,string XPathExpr){

	OptionReturnedFields.push_back("id");
	OptionReturnedFields.push_back("name");
	OptionReturnedFields.push_back("description");

	OptionWhereFields.push_back("active");
	OptionWhereFields.push_back("deleted");
	OptionWhereFields.push_back("domain");

	OptionWhereValues.push_back("1");
	OptionWhereValues.push_back("0");
	OptionWhereValues.push_back(XaDomain);
	
	OptionOrderByFields.push_back("position");

	DbResMap DbRes;

	XaLibSql* LibSql=new XaLibSql();
	DbRes=LibSql->Select(DB_READ,"XaDomain",OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);
	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=DbRes[n]["id"];
		string OptionLabel;
		if (XaDomain=="XaPhoneCode") {
			OptionLabel=DbRes[n]["description"]+" "+DbRes[n]["name"];
		} else {
			OptionLabel=DbRes[n]["name"]+" "+DbRes[n]["description"];
		}

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Domain-> "+ XaDomain + " - " + XPathExpr);
};

void XaLibAction::AddOptionsByVectors(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr){

	unsigned FieldsSize = this->XmlFields.size();
	unsigned ValuesSize = XmlValues.size();

	if(FieldsSize==ValuesSize && FieldsSize>0) {

		for(int n=0; n<FieldsSize; n++) {

			string Label=XmlFields.at(n).c_str();
			string Value=XmlValues.at(n).c_str();

			LibDom->AddOptionElementByXPath(XmlDomDoc,XPathExpr,Label,Value);
	    }
	}	

	XmlFields.erase (XmlFields.begin(),XmlFields.end());
	XmlValues.erase (XmlValues.begin(),XmlValues.end());

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Vectors-> "+ XPathExpr);
};

void XaLibAction::AddValuesByDb(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string TableName,string XPathExpr){
	
	OptionWhereFields.push_back("active");
	OptionWhereFields.push_back("deleted");

	OptionWhereValues.push_back("1");
	OptionWhereValues.push_back("0");

	//OptionOrderByFields.push_back("name");

	DbResMap DbRes;

	//ADD VALUE VALUE
	XaLibSql* LibSql=new XaLibSql();

	DbRes=LibSql->Select(DB_READ,TableName,OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);

	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string ValueValue=DbRes[n][OptionReturnedFields[0]];
		//string OptionLabel=DbRes[n]["name"];

		LibDom->AddValueElementByXPath(XmlDomDoc, XPathExpr,ValueValue);
	}

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();
	OptionOrderByFields.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options By Db-> "+ TableName + " - " + XPathExpr);
};

string XaLibAction::SelectDbItem(string ID,string TableName){

	OptionReturnedFields.push_back("name");
	OptionWhereFields.push_back("id");
	OptionWhereValues.push_back(ID);

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes=LibSql->Select(DB_READ,TableName,OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);	
	delete(LibSql);

	string ItemValue=DbRes[0]["name"];

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read Table -> "+ TableName +" Option Id -> "+ ID + " Value -> " + ItemValue);

	return ItemValue;
};

string XaLibAction::SelectDomainItem(string XaDomain_ID){

	OptionReturnedFields.push_back("name");
	OptionWhereFields.push_back("id");
	OptionWhereValues.push_back(XaDomain_ID);

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes=LibSql->Select(DB_READ,"XaDomain",OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);	
	delete(LibSql);

	string ItemValue=DbRes[0]["name"];

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read Option Id-> "+ XaDomain_ID + " value -> " + ItemValue);

	return ItemValue;
};

int XaLibAction::SelectDomainItemIdFromName(string domain, string name){

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes=LibSql->Select(DB_READ,"XaDomain",{"id"},{"domain","name"},{domain,name},{"id"});	
	delete(LibSql);

        if(DbRes.size()==1) {
            LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read Domain: Name-> " +name+ " From Domain " +domain+ ", id -> " +DbRes[0]["id"]);
            int ItemId=XaLibBase::FromStringToInt(DbRes[0]["id"]);
            return ItemId;
        } else {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Read Domain: Name-> " +name+ " From Domain " +domain+ ", Wrong Number of Rows Found : " +XaLibBase::FromIntToString(DbRes.size()));
            return 0;
        }
	DbRes.clear();

};

string XaLibAction::SelectUserItem(string XaUser_ID){

	OptionReturnedFields.push_back("name");
	OptionReturnedFields.push_back("surname");
	OptionWhereFields.push_back("id");
	OptionWhereValues.push_back(XaUser_ID);

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes=LibSql->Select(DB_READ,"XaUser",OptionReturnedFields,OptionWhereFields,OptionWhereValues,OptionOrderByFields);	
	delete(LibSql);

	string ItemValue=DbRes[0]["name"];
	if(DbRes[0]["name"]!="" && DbRes[0]["surname"]!="") { ItemValue+=" ";};
	ItemValue+=DbRes[0]["surname"];

	DbRes.clear();
	OptionReturnedFields.clear();
	OptionWhereFields.clear();
	OptionWhereValues.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read User Id-> "+ XaUser_ID + " full name -> " + ItemValue);

	return ItemValue;
};

string XaLibAction::HttpParamValidation (string ParamName, string ParamValue, string DataType, string Required, string Dimension, string Domain, string DefaultValue) {

	if (Required=="yes" && ParamValue=="NoHttpParam"){

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Validation Required Test Failed For Field: " + ParamName);
		//this->ErrorExit("XaInfoPage","HttpParamValidation");
	}

	if (Dimension!="" && ParamValue.size()>XaLibBase::FromStringToInt(Dimension)) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Validation Dimension Test Failed For Field: " + ParamName);
		//this->ErrorExit("XaInfoPage","HttpParamValidation");
	}

	if (DefaultValue!="" && ParamValue=="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Empty HttpParam value for -> "+ParamName+" replaced with default -> "+ DefaultValue);
		return DefaultValue;

	} else {

		return ParamValue;
	}

};

string XaLibAction::EncryptParam(string ClearValue){

	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string EncryptedValue=LibCrypto->AesEncrypt(ClearValue);
	delete(LibCrypto);

	//XaLibAction::LOG.Write(XaLibAction::MyLogFile,"INF", __FILE__, __FUNCTION__,__LINE__,"Crypted Param -> Clear Value: "+ ClearValue + " Encrypted Value: "+ EncryptedValue);

	XaLibChar* LibChar=new XaLibChar();
	string EncodedB64EncryptedValue=LibChar->B64Encode(EncryptedValue);
	//string B64CryptoXaUser_IDDec=LibChar->B64Decode(B64CryptoXaUser_ID);
	delete (LibChar);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"EnCrypted Parameter -> Clear Value: "+ ClearValue + " Encrypted Value: "+ EncryptedValue + "Encoded Value: "+ EncodedB64EncryptedValue);

	return EncodedB64EncryptedValue;
};

string XaLibAction::EncryptParam(int ClearValue){

	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string EncryptedValue=LibCrypto->AesEncrypt(XaLibBase::FromIntToString(ClearValue));
	delete(LibCrypto);

	//XaLibAction::LOG.Write(XaLibAction::MyLogFile,"INF", __FILE__, __FUNCTION__,__LINE__,"Crypted Param -> Clear Value: "+ XaLibBase::FromIntToString(ClearValue) + "Encrypted Value: "+ EncryptedValue);

	XaLibChar* LibChar=new XaLibChar();
	string EncodedB64EncryptedValue=LibChar->B64Encode(EncryptedValue);
	//string B64CryptoXaUser_IDDec=LibChar->B64Decode(B64CryptoXaUser_ID);
	delete (LibChar);

	//XaLibAction::LOG.Write(XaLibAction::MyLogFile,"INF", __FILE__, __FUNCTION__,__LINE__,"Encoded Param -> Encrypted Value: "+ EncryptedValue + "Encoded Value: "+ EncodedB64EncryptedValue);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"EnCrypted Parameter -> Clear Value: "+ XaLibBase::FromIntToString(ClearValue) + " Encrypted Value: "+ EncryptedValue + "Encoded Value: "+ EncodedB64EncryptedValue);

	return EncodedB64EncryptedValue;
};

string XaLibAction::DecryptParam(string EncryptedValue) {

	XaLibChar* LibChar=new XaLibChar();
	string DecodedB64EncryptedValue=LibChar->B64Decode(EncryptedValue);
	delete (LibChar);

	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string DecryptedValue=LibCrypto->AesDecrypt(DecodedB64EncryptedValue);
	delete(LibCrypto);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"DeCrypted Parameter -> Encrypted Value: "+ EncryptedValue + " Encoded Value: "+ DecodedB64EncryptedValue + " Clear Value: "+ DecryptedValue);

	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\n'), DecryptedValue.end());
	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\r'), DecryptedValue.end());
	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\0'), DecryptedValue.end());

	return DecryptedValue;
};

string XaLibAction::DecryptParamId(string EncryptedValue) {

	XaLibChar* LibChar=new XaLibChar();
	string DecodedB64EncryptedValue=LibChar->B64Decode(EncryptedValue);
	delete (LibChar);


	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string DecryptedValue=LibCrypto->AesDecrypt(DecodedB64EncryptedValue);
	delete(LibCrypto);

	//XaLibAction::LOG.Write(XaLibAction::MyLogFile,"INF", __FILE__, __FUNCTION__,__LINE__,"Crypted Param -> Encrypted Value: "+ DecodedB64EncryptedValue + "Clear Value: "+ DecryptedValue);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"DeCrypted Parameter -> Encoded Value: "+ EncryptedValue + " Encrypted Value: "+ DecodedB64EncryptedValue + " Clear Value: "+ DecryptedValue);

	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\n'), DecryptedValue.end());
	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\r'), DecryptedValue.end());
	DecryptedValue.erase(remove(DecryptedValue.begin(), DecryptedValue.end(), '\0'), DecryptedValue.end());

	int DecryptedValueInt=XaLibBase::FromStringToInt(DecryptedValue);
	string DecryptedValueString=XaLibBase::FromIntToString(DecryptedValueInt);

	return DecryptedValueString;
};



void XaLibAction::UpdateSessionWsLog (const string &XaSessionWsLog_ID,const string &Query,const string &Response) {
		
	vector<string> VectorFields{"log_data","response","response_time"};
	vector<string> VectorValues{Query,Response,XaLibTime::GetDateTimeMySql()};
	vector<string> WhereFields{"id"};
	vector<string> WhereValues{XaSessionWsLog_ID};		

	unique_ptr<XaLibSql> LibSql (new XaLibSql());
	LibSql->Update(DB_SESSION,"XaSessionWsLog",VectorFields,VectorValues,WhereFields,WhereValues);

	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
};

string XaLibAction::ComposeSearchCondition(string Value,string Field,string Type){
	
	string Condition;

	if (Type=="input-text") {
		Condition=" AND "+Field+" LIKE '%"+Value+"%'";
	} else if (Type=="input-select") {
		Condition=" AND "+Field+"="+Value;
	} else if (Type=="input-select-parent-user") {
		Condition=" AND "+Field+" LIKE '%|"+Value+"|%'";
	} else if (Type=="input-date-birth-user") {
		Condition=" AND "+Field+" >= '"+Value+"'";
	} else if (Type=="input-date-start-salary") {
		Condition=" AND "+Field+" >= '"+Value+"'";
	} else if (Type=="complete-address") {
		Condition=" AND (post_code LIKE '%"+Value+"%' OR address LIKE '%"+Value+"%')";
	} else if (Type=="quick-search-user") {
		Condition=" AND active=1 AND (name LIKE '%"+Value+"%' OR surname LIKE '%"+Value+"%')";
	} else {
		Condition="";
	}
	
	return Condition;

};

void XaLibAction::ResetRequest(){

	REQUEST.CalledEvent="";
	REQUEST.CalledObject="";
};
*/
/*
void XaLibAction::AddOptionsToModel(const string& FileModelPath,const string& XmlOptions,const string XPathExpr) {
	
	xmlDocPtr DocModel=LibDom.DomFromFile(Model[0]);

	//Retrieve Options for OuType
	XaLibCurl LibCurl;
	string CallResponse = LibCurl.Call(BuildBackEndCall("XaOuType","ListAsOptions",{},{}));
	CheckResponse(CallResponse);

	xmlDocPtr DocOptions=LibDom.DomFromString(CallResponse);

	int ElementsNumber=LibDom.GetNumRowByXPathInt(DocOptions,"/WsData/list/item");

	for (auto i=0;i<ElementsNumber;i++) {

		//LOADING PROPERTIES
		string FieldLabel=XaLibDom::GetElementValueByXPath(DocOptions,"/WsData/list/item["+ to_string(i+1) + "]/name");
		string FieldValue=XaLibDom::GetElementValueByXPath(DocOptions,"/WsData/list/item["+ to_string(i+1) + "]/id");

		OptionLabel.push_back(FieldLabel);
		OptionValue.push_back(FieldValue);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Loaded value for property ->" +FieldLabel +" :: " + FieldValue);
	};
	
	
	//LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"XXXXXXXXx -> "+CallResponse);

	string XPathExpr="//XaOu/fieldset/field[@id='XaOuType_ID']/options";
	
	
	
	
	LibDom.AddOptionElementByXPath(DocModel,XPathExpr,OptionLabel,OptionValue);


	string pippo=LibDom.StringFromDom(DocModel);

};
*/
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