#include <XaUserUi.h>
#include <XaLibAction.h>

XaUserUi::XaUserUi() {
};

void XaUserUi::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="LoginFrm"){
		this->LoginFrm();
	} else if (CalledEvent=="Login"){
		this->Login();
	} else if (CalledEvent=="Logout"){
		this->Logout();
	} else if (CalledEvent=="LogoutFrm"){
		this->LogoutFrm();
	} else if (CalledEvent=="List"){
		this->List();
	} else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserUi::LoginFrm () {

	string StrError=HTTP.GetHttpParam("LoginStatus");
	SetLayout("LoginFrm");
	AddXmlFile("LoginFrm");
	AddXslFile("LoginFrm");

	AddXslParamCommon();

	if (StrError=="error") {

		AddXslParam("LoginStatus","error");
	}

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
};

void XaUserUi::Login (){

	string StrUsername=HTTP.GetHttpParam("username");
	string StrPassword=HTTP.GetHttpParam("password");

	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCallLogin(StrUsername,StrPassword));
	CheckResponse(CallResponse);
	
	
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromString(CallResponse);
	string token=XaLibDom::GetElementValueByXPath(XmlDomDoc,"/WsData/token");

	if ( token=="ELEMENT-NOT-DEFINED" || token=="" || token.size()<FromStringToInt(SETTINGS["SessionIdLength"])) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Back End Login Action returned an error");

		RESPONSE.ResponseType="location";
		RESPONSE.Location="obj=XaUserUi&evt=LoginFrm";

	} else {

		SESSION.Token=token;
		RESPONSE.ResponseType="location";
		RESPONSE.Location="obj=XaPages&evt=XaMyPage";
		RESPONSE.Content=CallResponse;	
	}
};

void XaUserUi::Logout (){

	XaLibCurl LibCurl;
	string CallResponse= LibCurl.Call(BuildBackEndCall("XaUser","Logout",{},{}));

	RESPONSE.ResponseType="location";
	RESPONSE.Location="obj=XaUserUi&evt=LogoutFrm";
	RESPONSE.Content="";
};

void XaUserUi::LogoutFrm () {

	SetLayout("LoginFrm");
	AddXmlFile("LogoutFrm");
	AddXslFile("LogoutFrm");

	AddXslParamCommon();

	RESPONSE.Content=XaLibGui::CreateForm(XmlFiles,XmlStrings,XslFiles,XslStrings,XslParams);
};

/*
int XaUser::Authenticate (string StrEmail,string StrPassword) {

	if (StrEmail !="" && StrPassword !="") {

		XaLibCrypto* LibCrypto=new XaLibCrypto();
		string ShaPassword=LibCrypto->GetSha1(StrPassword);
		delete (LibCrypto);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Email -> "+StrEmail);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Password -> "+ShaPassword);

		DbResMap DbRes;

		unique_ptr<XaLibSql> LibSql (new XaLibSql());
			
		vector<string> ReturnedFields{"*"};
		vector<string> WhereFields{"email","password","active","deleted"};
		vector<string> WhereValues{StrEmail,ShaPassword,"1","0"};

		DbRes=LibSql->Select(DB_SESSION,"XaUser",ReturnedFields,WhereFields,WhereValues);

		ReturnedFields.clear();
		WhereFields.clear();
		WhereValues.clear();

		int n=DbRes.size();

		if (n==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"User Does Not Exist Or The Password Is Wrong -> " + StrEmail);
			return 0;

		} else if (n==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"User Is Valid -> Id is ->"+DbRes[0]["id"]);
			return XaLibBase::FromStringToInt(DbRes[0]["id"]);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"User Is Not Unique");
			return 0;
		}
		
	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Username Or Password Is Empty");
		return 0;
	}

};

void XaUser::XaUserLoginAddFrm() {

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserLogin");
	XaLibAction::AddXslFile("XaUserLoginTpl");
    XaLibAction::AddXslFile("XaUserLoginAddFrm");

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");
	
    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);

	//ADD OPTION XaUserProfile
	string XPathExprXaUserProfile="//field[@name='XaUserXaUserProfile-XaUserProfile_ID']/options";
	XaLibAction::AddOptionsByDbWithCondition(LibDom,XmlDomDoc,"XaUserProfile",XPathExprXaUserProfile," AND id>2");
	
	//ADD OPTION XaUser-Email
	string XPathExprType="//field[@name='XaUser-Email']/options";
	XaLibAction::OptionWhereFields.push_back("XaField_ID");
	XaLibAction::OptionWhereValues.push_back(XaLibAction::DecryptParamId(XaUser_ID));
	XaLibAction::OptionOrderByFields.push_back("email");
	XaLibAction::AddOptionsByDb(LibDom,XmlDomDoc,"XaAddressMail",XPathExprType,"id","email");
	
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

	if (XaUser_ID!="NoHttpParam"){

		const int MAXITEMS = 2;

		string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

		//XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};

void XaUser::XaUserLoginAdd(){

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	vector<string> XaUserProfile_ID=HTTP.GetHttpParamArray("XaUserXaUserProfile-XaUserProfile_ID");

	string EmailId=HTTP.GetHttpParam("XaUser-Email");
	string Password=HTTP.GetHttpParam("XaUser-Password");
	string Login=HTTP.GetHttpParam("XaUser-Login");

	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string ShaPassword=LibCrypto->GetSha1(Password);
	delete (LibCrypto);
	
	XaLibSql* LibSql=new XaLibSql();
	
	vector<string> WhereFields, WhereValues, ReturnedFields;
	
	ReturnedFields.push_back("email");
	
	WhereFields.push_back("id");
	WhereFields.push_back("active");
	WhereFields.push_back("deleted");
	
	WhereValues.push_back(EmailId);
	WhereValues.push_back("1");
	WhereValues.push_back("0");

	DbResMap DbResMail=LibSql->Select(DB_READ,"XaAddressMail",ReturnedFields,WhereFields,WhereValues);

	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	// ADD Account
	vector<string> VectorFields, VectorValues;
	
	VectorFields.push_back("email");
	VectorValues.push_back(DbResMail[0]["email"]);
	
	VectorFields.push_back("password");
	VectorValues.push_back(ShaPassword);

	VectorFields.push_back("last_updated");
	VectorValues.push_back(XaLibAction::NowTimeMysql);
	
	VectorFields.push_back("login");
	VectorValues.push_back(Login);

	WhereFields.push_back("id");
	WhereValues.push_back(XaUser_ID);
		
	int UpdateId=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
	
	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
	
		string Res;
		
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Employee - Add Account ID -> "+XaUser_ID);
			Res="error adding Account";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Employee - Add Account ID -> "+XaUser_ID);
			Res="Account successfully added";
			
			// ADD in XaUserXaUserProfile
			for(unsigned n=0; n<XaUserProfile_ID.size(); ++n) {
				this->XaUserXaUserProfileAdd(XaLibBase::FromStringToInt(XaUser_ID),XaLibBase::FromStringToInt(XaUserProfile_ID[n]));
			}
	
		}
	
	RESPONSE.Content=Res;
};

void XaUser::XaUserLoginModFrm() {

    XaLibAction::SetLayout("Included");

    XaLibAction::AddXmlFile("XaUserLoginModFrm");
	XaLibAction::AddXslFile("XaUserLoginModFrmTpl");
    XaLibAction::AddXslFile("XaUserLoginModFrm");
	
	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	
    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
    xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	//ADD OPTION XaUserProfile
	string XPathExprXaUserProfile="//field[@name='XaUserXaUserProfile-XaUserProfile_ID']/options";
	XaLibAction::AddOptionsByDbWithCondition(LibDom,XmlDomDoc,"XaUserProfile",XPathExprXaUserProfile," AND id>2");
	
	//ADD OPTION XaUser-Email
	string XPathExprType="//field[@name='XaUser-Email']/options";
	XaLibAction::OptionWhereFields.push_back("XaField_ID");
	XaLibAction::OptionWhereValues.push_back(XaUser_ID);
	XaLibAction::OptionOrderByFields.push_back("email");
	XaLibAction::AddOptionsByDb(LibDom,XmlDomDoc,"XaAddressMail",XPathExprType,"id","email");
	
	
	XaLibSql* LibSql=new XaLibSql();

	string QryUser="SELECT id,email,login FROM XaUser WHERE XaUserType_ID=3 AND id="+ XaUser_ID +" AND deleted=0 AND active=1";
	
	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

		// ADD Selected values
		if (DbResUser.size()==1) {
			
			string XPathExprXaUserXaUserProfile="//field[@name='XaUserXaUserProfile-XaUserProfile_ID']/values";
			XaLibAction::OptionWhereFields.push_back("XaUser_ID");
			XaLibAction::OptionWhereValues.push_back(XaUser_ID);
			XaLibAction::OptionReturnedFields.push_back("XaUserProfile_ID");
			XaLibAction::AddValuesByDb(LibDom,XmlDomDoc,"XaUserXaUserProfile",XPathExprXaUserXaUserProfile);
			
			string QryMail="SELECT id FROM XaAddressMail WHERE XaField_ID="+ XaUser_ID +" AND email='"+ DbResUser[0]["email"] +"' AND deleted=0 AND active=1";
			DbResMap DbResMail=LibSql->FreeQuery(DB_READ,QryMail);
			string EmailId="";
			if (DbResMail.size()==1) {
				EmailId=DbResMail[0]["id"];
			}
			
			string ArrayXPathExpr[] = {"//field[@id='XaUser-Email']/value","//field[@id='XaUser-Login']/value"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+2);

			string ArrayXPathValue[] = {EmailId,DbResUser[0]["login"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+2);

			LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

		}

	delete(LibDom);

	if (XaUser_ID!="NoHttpParam"){

		const int MAXITEMS = 2;

		string XslParams[MAXITEMS] = {"XaUser_ID",HTTP.GetHttpParam("XaUser_ID")};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

//		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};

void XaUser::XaUserLoginMod(){

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	vector<string> XaUserProfile_ID=HTTP.GetHttpParamArray("XaUserXaUserProfile-XaUserProfile_ID");

	string EmailId=HTTP.GetHttpParam("XaUser-Email");
	string Password=HTTP.GetHttpParam("XaUser-Password");
	string Login=HTTP.GetHttpParam("XaUser-Login");
	
	XaLibSql* LibSql=new XaLibSql();
	
	vector<string> WhereFields, WhereValues, ReturnedFields;
	
	ReturnedFields.push_back("email");
	
	WhereFields.push_back("id");
	WhereFields.push_back("active");
	WhereFields.push_back("deleted");
	
	WhereValues.push_back(EmailId);
	WhereValues.push_back("1");
	WhereValues.push_back("0");

	DbResMap DbResMail=LibSql->Select(DB_READ,"XaAddressMail",ReturnedFields,WhereFields,WhereValues);

	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	// MOD Account
	vector<string> VectorFields, VectorValues;
	
	VectorFields.push_back("email");
	VectorValues.push_back(DbResMail[0]["email"]);
	
	if(Password!="") {
		XaLibCrypto* LibCrypto=new XaLibCrypto();
		string ShaPassword=LibCrypto->GetSha1(Password);
		delete (LibCrypto);
	
		VectorFields.push_back("password");
		VectorValues.push_back(ShaPassword);	
	}

	VectorFields.push_back("login");
	VectorValues.push_back(Login);
	
	VectorFields.push_back("last_updated");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	WhereFields.push_back("id");
	WhereValues.push_back(XaUser_ID);
		
	int UpdateId=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
	
	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
	
		string Res;
		
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Employee - Mod Account ID -> "+XaUser_ID);
			Res="error modifying account";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Employee - Mod Account ID -> "+XaUser_ID);
			Res="account successfully modified";
			
			// DEL XaUserXaUserProfile
			string QryProfile="SELECT id FROM XaUserXaUserProfile WHERE XaUser_ID="+ XaUser_ID +" AND deleted=0 AND active=1 AND XaUserProfile_ID>2";
			DbResMap DbResProfile=LibSql->FreeQuery(DB_READ,QryProfile);
			
			for(unsigned i=0; i<DbResProfile.size(); ++i){
				WhereFields.push_back("id");
				WhereValues.push_back(DbResProfile[i]["id"]);
					
				LibSql->Delete(DB_WRITE,"XaUserXaUserProfile",WhereFields,WhereValues);
				
				WhereFields.clear();
				WhereValues.clear();
			}
			
			// ADD in XaUserXaUserProfile
			for(unsigned n=0; n<XaUserProfile_ID.size(); ++n) {
				this->XaUserXaUserProfileAdd(XaLibBase::FromStringToInt(XaUser_ID),XaLibBase::FromStringToInt(XaUserProfile_ID[n]));
			}
	
		}
	
	RESPONSE.Content=Res;

};

void XaUser::XaUserLoginView (){
        
	XaLibAction::SetLayout("Included");
	XaLibAction::AddXslFile("XaUserLoginViewIncluded");

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("RowId"));
	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserLoginViewData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string Editable="no";
	
	vector<string> ReturnedFields, WhereFields, WhereValues;
	ReturnedFields.push_back("id");
	WhereFields.push_back("id");
	WhereValues.push_back(XaUser_ID);
	WhereFields.push_back("active");
	WhereValues.push_back("1");
	WhereFields.push_back("deleted");
	WhereValues.push_back("0");

	DbResMap DbResEmployee=LibSql->Select(DB_READ,"XaUser",ReturnedFields,WhereFields,WhereValues);
	
	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	if (DbResEmployee.size()==1) {
		Editable="yes";
	}
	//

	string QryUser="SELECT id,email,login FROM XaUser WHERE XaUserType_ID=3 AND id="+ XaUser_ID +" AND login IN (1,0) AND deleted=0"; // AND active=1 tolta per vedere i dati degli utenti con contratto chiuso active=3
	
	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

		if (DbResUser.size()==1) {
			
			string XaUserProfile="";
			string QryProfile="SELECT name FROM XaUserXaUserProfile r,XaUserProfile p WHERE r.XaUser_ID="+ XaUser_ID  +" AND r.XaUserProfile_ID=p.id AND r.active=1 AND r.deleted=0 ORDER BY name";
	
			DbResMap DbResProfile=LibSql->FreeQuery(DB_READ,QryProfile);
			
			for (int l=0; l<DbResProfile.size();l++) {
				XaUserProfile+=DbResProfile[l]["name"] + ", ";	
			}
			int XaUserProfileSize=XaUserProfile.size()-2;
			XaUserProfile=XaUserProfile.substr (0,XaUserProfileSize);
			
			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserLoginView/data/user/";
			string ArrayXPathExpr[] = {XPB+"XaUser-Id",XPB+"XaUser-Email",XPB+"XaUser-XaUserProfile",XPB+"XaUser-Login"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+4);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResUser[0]["id"]),DbResUser[0]["email"],XaUserProfile,DbResUser[0]["login"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+4);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		} else {
			//NOT UNIQUE
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 4;
    string XslParams[MAXITEMS] = {"XaUser_ID",HTTP.GetHttpParam("RowId"),"Editable",Editable};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserLoginList (){

	string StrFromYear=HTTP.GetHttpParam("from_year");
	string StrToYear=HTTP.GetHttpParam("to_year");
	string StrFromMonth=HTTP.GetHttpParam("from_month");
	string StrToMonth=HTTP.GetHttpParam("to_month");
	string Login=HTTP.GetHttpParam("XaUser-Login");
	
	XaLibAction::SetLayout("Standard");
    XaLibAction::AddXslFile("XaUserLoginList");

    XaLibAction::AddXmlFile("XaUserLoginListStruct");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserLoginListData.xml");
	
	string Cond;
	
	if (Login!="" && Login!="NoHttpParam") {
		Cond=" AND login="+Login;
	} else {
		Cond="";
	}

	XaLibSql* LibSql=new XaLibSql();

	string QryUser="SELECT id,email,login,name,surname FROM XaUser WHERE XaUserType_ID=3 AND deleted=0 AND active=1 AND email!='' AND email IS NOT NULL" +Cond;
	QryUser+=" ORDER BY surname";
	
	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

		for (int i=0;i<DbResUser.size();i++) {

			string XaUserProfile="";
			string QryProfile="SELECT name FROM XaUserXaUserProfile r,XaUserProfile p WHERE r.XaUser_ID="+ DbResUser[i]["id"] +" AND r.XaUserProfile_ID=p.id AND r.active=1 AND r.deleted=0 ORDER BY name";
	
			DbResMap DbResProfile=LibSql->FreeQuery(DB_READ,QryProfile);
			
			for (int l=0; l<DbResProfile.size();l++) {
				XaUserProfile+=DbResProfile[l]["name"] + ", ";	
			}
			int XaUserProfileSize=XaUserProfile.size()-2;
			XaUserProfile=XaUserProfile.substr (0,XaUserProfileSize);
			
			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserLoginList/data/user/";
			string ArrayXPathExpr[] = {XPB+"XaUser-Id",XPB+"XaUser-Email",XPB+"XaUser-XaUserProfile",XPB+"XaUser-Login",XPB+"XaUser-Name",XPB+"XaUser-Surname"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+6);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResUser[i]["id"]),DbResUser[i]["email"],XaUserProfile,DbResUser[i]["login"],DbResUser[i]["name"],DbResUser[i]["surname"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+6);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
			
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
		
		string XPB1="/root/XaUserLoginList/fieldset/";
		string r1 =XPB1+"field[@name='XaUser-Login']/value";								
		
		string ArrayXPathExpr1[] = {r1};
		vector<string> XPathExpr1(ArrayXPathExpr1, ArrayXPathExpr1+1);
		
		string s1 =Login;
		
		string ArrayXPathValue1[] = {s1};
		vector<string> XPathValue1(ArrayXPathValue1, ArrayXPathValue1+1);
	
		LibDom->UpdateElementValueByXPath(XmlDomDoc, XPathExpr1, XPathValue1);
		
		XPathExpr1.clear();
		XPathValue1.clear();
		
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserLoginRowMod(){

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string Login=HTTP.GetHttpParam("XaUser-Login");
	
	XaLibSql* LibSql=new XaLibSql();
		
	// MOD Login
	vector<string> VectorFields, VectorValues, WhereFields, WhereValues;

	VectorFields.push_back("login");
	VectorValues.push_back(Login);
	
	VectorFields.push_back("last_updated");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	WhereFields.push_back("id");
	WhereValues.push_back(XaUser_ID);
		
	int UpdateId=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
	
	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
	
		string Res;
		
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Employee - Mod field Login ID -> "+XaUser_ID);
			Res="error modifying user login";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Employee - Mod field Login ID -> "+XaUser_ID);
			Res="user login successfully modified";
	
		}

	RESPONSE.Content=Res;

};

void XaUser::XaUserPasswordModFrm() {

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserPasswordModFrm");
	XaLibAction::AddXslFile("XaUserPasswordModFrmTpl");
    XaLibAction::AddXslFile("XaUserPasswordModFrm");
	
	//string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string XaUser_ID=FromIntToString(REQUEST.XaUser_ID);
    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
    xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	delete(LibDom);

	if (XaUser_ID!="NoHttpParam"){

		const int MAXITEMS = 2;

		string XslParams[MAXITEMS] = {"XaUser_ID",XaLibAction::EncryptParam(REQUEST.XaUser_ID)};
		XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
		RESPONSE.Content=LibXsl->GetXHtml();
		delete(LibXsl);

	} else {

//		XaLibAction::ErrorExit("XaInfoPage","GetHttpParam");
	}

};

void XaUser::XaUserPasswordMod(){

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
	string NewPassword=HTTP.GetHttpParam("XaUser-NewPassword");
	string Password=HTTP.GetHttpParam("XaUser-Password");
	
	XaLibSql* LibSql=new XaLibSql();
	
	XaLibCrypto* LibCrypto=new XaLibCrypto();
	string ShaPassword=LibCrypto->GetSha1(Password);
	string ShaNewPassword=LibCrypto->GetSha1(NewPassword);
	delete (LibCrypto);
			
	string Qry="SELECT password FROM XaUser WHERE password='"+ ShaPassword + "' AND id=" +XaUser_ID+ " AND active=1 AND deleted=0";
				
	DbResMap DbRes=LibSql->FreeQuery(DB_SESSION,Qry);
	
	string Res;	
		
	if (DbRes.size()==1) {
		
                unique_ptr<XaLibTime> LibTime (new XaLibTime());
                string NowTimeMysql=LibTime->GetDateTimeMySql();
		
                // MOD Password
		vector<string> VectorFields, VectorValues, WhereFields, WhereValues;
	
		VectorFields.push_back("password");
		VectorValues.push_back(ShaNewPassword);
		
		VectorFields.push_back("last_updated");
		VectorValues.push_back(NowTimeMysql);
	
		WhereFields.push_back("id");
		WhereValues.push_back(XaUser_ID);
			
		int UpdateId=LibSql->Update(DB_SESSION,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
		
		VectorFields.clear();
		VectorValues.clear();
		WhereFields.clear();
		WhereValues.clear();
	
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Mod Password - User ID -> "+XaUser_ID);
			Res="error modifying user password";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Mod Password - User ID -> "+XaUser_ID);
			Res="user password successfully modified";
	
		}
	
	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Mod Password - User ID -> "+XaUser_ID);
		Res="error modifying user password";
	
	}
	
	RESPONSE.Content=Res;

};

void XaUser::XaUserCompanyAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserCompany");
    
    XaLibAction::AddXslFile("XaUserCompanyTpl");
    XaLibAction::AddXslFile("XaUserCompanyAddFrm");
    
    XaLibDom* LibDom=new XaLibDom();
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserCompanyAdd () {

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserCompany.xml");

	string StrArrKey[] = {"name","dbname","datatype","required","dimension","domain","default"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 7);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	vector<string> VectorFields, VectorValues;

	for(unsigned i=0; i<ParamFromDom.size(); ++i){

		string ParamValue=HTTP.GetHttpParam(ParamFromDom[i]["name"]);
		ParamValue=XaLibAction::HttpParamValidation(ParamFromDom[i]["name"],ParamValue,ParamFromDom[i]["datatype"],ParamFromDom[i]["required"],ParamFromDom[i]["dimension"],ParamFromDom[i]["domain"],ParamFromDom[i]["default"]);

		VectorFields.push_back(ParamFromDom[i]["dbname"]);
		VectorValues.push_back(ParamValue);
	}

		VectorFields.push_back("tree_parent_id");
		VectorValues.push_back("1");

		VectorFields.push_back("XaUserRole_ID");
		VectorValues.push_back("1");

		VectorFields.push_back("XaUserType_ID");
		VectorValues.push_back("1");
	
		VectorFields.push_back("leaf");
		VectorValues.push_back("0");

		VectorFields.push_back("active");
		VectorValues.push_back("1");

		VectorFields.push_back("deleted");
		VectorValues.push_back("0");

		VectorFields.push_back("created");
		VectorValues.push_back(XaLibAction::NowTimeMysql);

		XaLibSql* LibSql=new XaLibSql();
		int NextId=LibSql->Insert(DB_WRITE,"XaUser",VectorFields,VectorValues);
		delete (LibSql);

		if(NextId==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting Company");

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted Company ID -> "+ XaLibBase::FromIntToString(NextId));

			this->UpdateTreeData(1,NextId);
			//this->XaUserXaUserProfileAdd(NextId,1);
		}

	ParamFromDom.clear();
	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content=XaLibAction::EncryptParam(NextId);
};

void XaUser::XaUserCompanyModFrm (){

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

/// prendere layout da HttpParam
	XaLibAction::SetLayout("Included");
    
	XaLibAction::AddXslFile("XaUserCompanyTpl");
	XaLibAction::AddXslFile("XaUserCompanyModFrmIncluded");
    
	XaLibDom* LibDom=new XaLibDom();

	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserCompany.xml");

	XaLibSql* LibSql=new XaLibSql();
	string QryUser="SELECT * FROM XaUser WHERE XaUserType_ID=1 AND id="+ XaLibAction::DecryptParamId(XaUser_ID) +" AND active=1 AND deleted=0";

	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

	for (int l=0; l<DbResUser.size();l++) {
		string XPB="//fieldset[@id='XaUserCompany']/";
		string r1 =XPB+"field[@id='XaUser-Surname']/value";
		string r2 =XPB+"field[@id='XaUser-Registration_Number']/value";
		string r3 =XPB+"field[@id='XaUser-Vat_Account']/value";

		string ArrayXPathExpr[] = {r1,r2,r3};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+3);

		string s1 =DbResUser[l]["surname"];
		string s2 =DbResUser[l]["registration_number"];
		string s3 =DbResUser[l]["vat_account"];

		string ArrayXPathValue[] = {s1,s2,s3};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+3);

		xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

		LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));

		XPathExpr.clear();
		XPathValue.clear();

	}

	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	delete(LibDom);

	const int MAXITEMS = 2;
	string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID};
	XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
	RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};


void XaUser::XaUserCompanyMod () {

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserCompany.xml");

	string StrArrKey[] = {"name","dbname","datatype","required","dimension","domain","default"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 7);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	vector<string> VectorFields, VectorValues;
	vector<string> WhereFields, WhereValues;

	for(unsigned i=0; i<ParamFromDom.size(); ++i){
		if (ParamFromDom[i]["name"]!="XaUser_ID") {
			string ParamValue=HTTP.GetHttpParam(ParamFromDom[i]["name"]);
			ParamValue=XaLibAction::HttpParamValidation(ParamFromDom[i]["name"],ParamValue,ParamFromDom[i]["datatype"],ParamFromDom[i]["required"],ParamFromDom[i]["dimension"],ParamFromDom[i]["domain"],ParamFromDom[i]["default"]);
	
			VectorFields.push_back(ParamFromDom[i]["dbname"]);
			VectorValues.push_back(ParamValue);
		}
	}

		VectorFields.push_back("active");
		VectorValues.push_back("1");

		VectorFields.push_back("deleted");
		VectorValues.push_back("0");

		// where
		string DecryptedXaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
		WhereFields.push_back("id");
		WhereValues.push_back(DecryptedXaUser_ID);

		XaLibSql* LibSql=new XaLibSql();
		int UpdateId=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
		delete (LibSql);

		if(UpdateId==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Company ID -> " + DecryptedXaUser_ID);

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Company ID -> "+ DecryptedXaUser_ID);

		}

	ParamFromDom.clear();
	VectorFields.clear();
	VectorValues.clear();

	// spostae messaggio di success/failure dentro if
	RESPONSE.Content="Company modified";
};


void XaUser::XaUserCompanyList (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserCompanyListStruct");
    XaLibAction::AddXslFile("XaUserCompanyList");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserCompanyListData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string QryCompanies="SELECT * FROM XaUser WHERE XaUserType_ID=1 AND deleted=0 ORDER BY surname";
	
	DbResMap DbResCompanies=LibSql->FreeQuery(DB_READ,QryCompanies);

		for (int i=0;i<DbResCompanies.size();i++) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserCompanyList/data/company/";
			string ArrayXPathExpr[] = {XPB+"XaUser-Id",XPB+"XaUser-Surname",XPB+"XaUser-Registration_Number",XPB+"XaUser-Vat_Account",XPB+"XaUser-Created",XPB+"XaUser-Last_Updated",XPB+"XaUser-Active"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+7);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResCompanies[i]["id"]),DbResCompanies[i]["surname"],DbResCompanies[i]["registration_number"],DbResCompanies[i]["vat_account"],DbResCompanies[i]["created"],DbResCompanies[i]["last_updated"],DbResCompanies[i]["active"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+7);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			//RETRIEVE GEO
			string QryAddressGeo="SELECT id,address,XaDomainType_ID FROM XaAddressGeo WHERE active=1 AND deleted=0 AND XaTable='XaUser' AND XaField_ID="+DbResCompanies[i]["id"];
			DbResMap DbResAddressGeo=LibSql->FreeQuery(DB_READ,QryAddressGeo);

			for (int j=0; j<DbResAddressGeo.size();j++) {
				string Type=XaLibAction::SelectDomainItem(DbResAddressGeo[j]["XaDomainType_ID"]);
				LibDom->AddAddressElementByXPath(XmlDomDocDataTemp,"//XaUserCompanyList/data/company/XaAddressGeo", DbResAddressGeo[j]["id"],Type,DbResAddressGeo[j]["address"]);

			}
			
			
			string QryAddressPhone="SELECT XaAddressPhone.id AS id,XaDomain.name AS country,XaAddressPhone.number AS number,XaAddressPhone.XaDomainType_ID "
					"FROM XaAddressPhone,XaDomain "
					"WHERE XaAddressPhone.deleted=0 AND XaAddressPhone.active=1 "
					"AND XaAddressPhone.XaDomainCode_ID=XaDomain.id "
					"AND XaAddressPhone.XaTable='XaUser' AND XaAddressPhone.XaField_ID="+DbResCompanies[i]["id"];
			
			DbResMap DbResAddressPhone=LibSql->FreeQuery(DB_READ,QryAddressPhone);
			
			for (int k=0; k<DbResAddressPhone.size();k++) {
				string Type=XaLibAction::SelectDomainItem(DbResAddressPhone[k]["XaDomainType_ID"]);
				string phone=DbResAddressPhone[k]["country"] +" "+DbResAddressPhone[k]["number"];
				LibDom->AddAddressElementByXPath(XmlDomDocDataTemp,"//XaUserCompanyList/data/company/XaAddressPhone", XaLibAction::EncryptParam(DbResAddressPhone[k]["id"]),Type,phone);

			}

			string QryAddressMail="SELECT id,email,XaDomainType_ID FROM XaAddressMail WHERE active=1 AND deleted=0 AND XaTable='XaUser' AND XaField_ID="+DbResCompanies[i]["id"];
			DbResMap DbResAddressMail=LibSql->FreeQuery(DB_READ,QryAddressMail);

			for (int l=0; l<DbResAddressMail.size();l++) {
				string Type=XaLibAction::SelectDomainItem(DbResAddressMail[l]["XaDomainType_ID"]);
				LibDom->AddAddressElementByXPath(XmlDomDocDataTemp,"//XaUserCompanyList/data/company/XaAddressMail", DbResAddressMail[l]["id"],Type,DbResAddressMail[l]["email"]);
			}

			string ArrayXPathExprID[] = {"//XaUserCompanyList/data/actions/action/id"};
			vector<string> XPathExprID(ArrayXPathExprID, ArrayXPathExprID+1);

			string ArrayXPathValueID[] = {XaLibAction::EncryptParam(DbResCompanies[i]["id"])};
			vector<string> XPathValueID(ArrayXPathValueID, ArrayXPathValueID+1);

			
			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp,XPathExprID,XPathValueID);
			
			XPathExprID.clear();
			XPathValueID.clear();
			//RIMUOVERE INTESTAZIONE XML
			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserCompanyView (){

	string LayoutType=HTTP.GetHttpParam("LayoutType");
    
    XaLibAction::AddXmlFile("XaUserCompanyViewStruct");
    
    if(LayoutType=="Included"){
		XaLibAction::SetLayout("Included");
		XaLibAction::AddXslFile("XaUserCompanyViewIncluded");
	} else {
		XaLibAction::SetLayout("ModalWindow");
		XaLibAction::AddXslFile("XaUserCompanyView");
	}

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("RowId"));
	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserCompanyViewData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string QryCompany="SELECT * FROM XaUser WHERE XaUserType_ID=1 AND id="+ XaUser_ID +" AND deleted=0";
	
	DbResMap DbResCompany=LibSql->FreeQuery(DB_READ,QryCompany);

		if (DbResCompany.size()==1) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserCompanyView/data/company/";
			string ArrayXPathExpr[] = {XPB+"XaUser-Id",XPB+"XaUser-Surname",XPB+"XaUser-Registration_Number",XPB+"XaUser-Vat_Account",XPB+"XaUser-Created",XPB+"XaUser-Last_Updated",XPB+"XaUser-Active"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+7);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResCompany[0]["id"]),DbResCompany[0]["surname"],DbResCompany[0]["registration_number"],DbResCompany[0]["vat_account"],DbResCompany[0]["created"],DbResCompany[0]["last_updated"],DbResCompany[0]["active"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+7);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			string ArrayXPathExprID[] = {"//XaUserCompanyView/data/actions/action/id"};
			vector<string> XPathExprID(ArrayXPathExprID, ArrayXPathExprID+1);

			string ArrayXPathValueID[] = {XaLibAction::EncryptParam(DbResCompany[0]["id"])};
			vector<string> XPathValueID(ArrayXPathValueID, ArrayXPathValueID+1);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp,XPathExprID,XPathValueID);
			
			XPathExprID.clear();
			XPathValueID.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		} else {
			//NOT UNIQUE
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		//LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,LibDom->StringFromDom(XmlDomDoc));
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"XaUser_ID",HTTP.GetHttpParam("RowId")};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

XaUser::DbResMap XaUser::GetXaUserList(string XaUserType,string Field,string Value,string ResField,string OrderBy,string Condition,string Filter){
	
	string Cond="";
	if (Field=="tree_path"){
		Cond.append(" AND tree_path LIKE '%|"+Value+"|%'");
	} else if (Field=="tree_parent_ID"){
		Cond.append(" AND tree_parent_ID="+Value);
	}
	
	Cond.append(Condition);
	
	if (Filter!=""){
		Cond.append(" AND id IN (SELECT XaField_ID FROM XaUserSalary WHERE XaTable='XaUser' AND active=1 AND deleted=0 "+Filter+")");
	}
	
	if (OrderBy!=""){
		Cond.append(" ORDER BY "+OrderBy);
	}
	
	string Qry="SELECT "+ResField+" FROM XaUser WHERE XaUserType_ID IN ("+XaUserType+")  AND active=1 AND deleted=0 "+Cond;
	
	XaLibSql* LibSql=new XaLibSql();

	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

	delete(LibSql);
	
	return DbRes;

};

string XaUser::GetTreeParentType(string TreeParentID){
	
	string TreeParentType;
	
	string Qry="SELECT tree_level FROM XaUser WHERE id = "+TreeParentID;
	
	XaLibSql* LibSql=new XaLibSql();

	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

	delete(LibSql);
	
	if (DbRes[0]["tree_level"]=="2") {
		TreeParentType="Company";
	} else if (DbRes[0]["tree_level"]=="3") {
		TreeParentType="Department";
	}else if (DbRes[0]["tree_level"]=="4") {
		TreeParentType="Section";
	}else {
		TreeParentType="CompanyOrDepartment";
	}
	
	return TreeParentType;

};

string XaUser::GetTreeParentId(string XaUserId,string XaUserTypeId){
	
	string TreeParentId="0";
	
	string Qry="SELECT tree_parent_ID FROM XaUser WHERE XaUserType_ID="+XaUserTypeId+" AND id="+XaUserId+" AND active=1 AND deleted=0";
	
	XaLibSql* LibSql=new XaLibSql();

	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

	delete(LibSql);
	
	if (DbRes.size()==1){
		TreeParentId=DbRes[0]["tree_parent_ID"];
	}
	
	return TreeParentId;

};

string XaUser::ComposeXaUserBreadcrumb(string TreeParentID){
	
	string XaUserBreadcrumb;
	
	string Qry="SELECT tree_level FROM XaUser WHERE id = "+TreeParentID;
	
	XaLibSql* LibSql=new XaLibSql();

	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

	delete(LibSql);
	
	if (DbRes[0]["tree_level"]=="2") {
		// Company
		XaUserBreadcrumb=XaLibAction::SelectUserItem(TreeParentID);
	} else if (DbRes[0]["tree_level"]=="3") {
		// Department
		string XaUserTypeId="2";
		string CompanyId=this->GetTreeParentId(TreeParentID,XaUserTypeId);
		XaUserBreadcrumb=XaLibAction::SelectUserItem(CompanyId)+"/"+XaLibAction::SelectUserItem(TreeParentID);	
	}else if (DbRes[0]["tree_level"]=="4") {
		// Section
		string XaUserTypeId="2";
		string DepartmentId=this->GetTreeParentId(TreeParentID,XaUserTypeId);
		string CompanyId=this->GetTreeParentId(DepartmentId,XaUserTypeId);
		XaUserBreadcrumb=XaLibAction::SelectUserItem(CompanyId)+"/"+XaLibAction::SelectUserItem(DepartmentId)+"/"+XaLibAction::SelectUserItem(TreeParentID);
	}else {
		XaUserBreadcrumb="";
	}
	
	return XaUserBreadcrumb;

};


void XaUser::XaUserDepartmentAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserDepartment");

    XaLibAction::AddXslFile("XaUserDepartmentTpl");
    XaLibAction::AddXslFile("XaUserDepartmentAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);

	this->GetMyChildren("XaUser","/",REQUEST.XaUser_ID);

		string XPathExprTreeParentID="/root/fieldset[@id='XaUserDepartment']/field[@name='tree_parent_ID']/options";
		XaLibAction::AddOptionsByVectors(LibDom,XmlDomDoc,XPathExprTreeParentID);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserDepartmentAdd () {
	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserDepartment.xml");

	string StrArrKey[] = {"name","dbname","datatype","required","dimension","domain","default"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 7);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	vector<string> VectorFields, VectorValues;

	for(unsigned i=0; i<ParamFromDom.size(); ++i){

		string ParamValue=HTTP.GetHttpParam(ParamFromDom[i]["name"]);
		ParamValue=XaLibAction::HttpParamValidation(ParamFromDom[i]["name"],ParamValue,ParamFromDom[i]["datatype"],ParamFromDom[i]["required"],ParamFromDom[i]["dimension"],ParamFromDom[i]["domain"],ParamFromDom[i]["default"]);

		VectorFields.push_back(ParamFromDom[i]["dbname"]);
		//VectorValues.push_back(ParamValue);
		
		string ParamName=ParamFromDom[i]["name"];
		
		if (ParamName=="tree_parent_ID") {
			VectorValues.push_back(XaLibAction::DecryptParamId(ParamValue));
		} else {
			VectorValues.push_back(ParamValue);
		}
		
	}

		//VectorFields.push_back("tree_parent_id");
		//VectorValues.push_back("1");

		VectorFields.push_back("XaUserRole_ID");
		VectorValues.push_back("1");

		VectorFields.push_back("XaUserType_ID");
		VectorValues.push_back("2");
	
		VectorFields.push_back("leaf");
		VectorValues.push_back("0");

		VectorFields.push_back("active");
		VectorValues.push_back("1");

		VectorFields.push_back("deleted");
		VectorValues.push_back("0");

		VectorFields.push_back("created");
		VectorValues.push_back(XaLibAction::NowTimeMysql);

		XaLibSql* LibSql=new XaLibSql();
		int NextId=LibSql->Insert(DB_WRITE,"XaUser",VectorFields,VectorValues);
		delete (LibSql);

		if(NextId==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting Department");

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted Department ID -> "+ XaLibBase::FromIntToString(NextId));

			int TreeParentID=XaLibBase::FromStringToInt(XaLibAction::DecryptParamId(HTTP.GetHttpParam("tree_parent_ID")));
			this->UpdateTreeData(TreeParentID,NextId);

			//this->XaUserXaUserProfileAdd(NextId,1);
		}

	ParamFromDom.clear();
	VectorFields.clear();
	VectorValues.clear();

	RESPONSE.Content=XaLibAction::EncryptParam(NextId);
};

void XaUser::XaUserDepartmentModFrm (){

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

/// prendere layout da HttpParam
    XaLibAction::SetLayout("Included");

    XaLibAction::AddXslFile("XaUserDepartmentTpl");
    XaLibAction::AddXslFile("XaUserDepartmentModFrmIncluded");
    
    XaLibDom* LibDom=new XaLibDom();

	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserDepartment.xml");

	XaLibSql* LibSql=new XaLibSql();
	string QryUser="SELECT * FROM XaUser WHERE XaUserType_ID=2 AND id="+ XaLibAction::DecryptParamId(XaUser_ID) +" AND active=1 AND deleted=0";

	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

	for (int l=0; l<DbResUser.size();l++) {
		string XPB="//fieldset[@id='XaUserDepartment']/";
		string r1 =XPB+"field[@id='XaUser-Surname']/value";
		string r2 =XPB+"field[@id='tree_parent_ID']/value";
		string r3 =XPB+"field[@id='tree_parent_ID']/disabled";

		string ArrayXPathExpr[] = {r1,r2,r3};
		vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+3);

		string s1 =DbResUser[l]["surname"];
		string s2 =XaLibAction::EncryptParam(DbResUser[l]["tree_parent_ID"]);
		string s3 ="yes";

		string ArrayXPathValue[] = {s1,s2,s3};
		vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+3);
		xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);

		LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));

		XPathExpr.clear();
		XPathValue.clear();

	}

	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	this->GetMyChildren("XaUser","/",REQUEST.XaUser_ID);
	string XPathExprTreeParentID="/root/fieldset[@id='XaUserDepartment']/field[@name='tree_parent_ID']/options";
	XaLibAction::AddOptionsByVectors(LibDom,XmlDomDoc,XPathExprTreeParentID);

	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"XaUser_ID",XaUser_ID};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};


void XaUser::XaUserDepartmentMod () {

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserDepartment.xml");

	string StrArrKey[] = {"name","dbname","datatype","required","dimension","domain","default"};
	vector<string> Vectorkey(StrArrKey, StrArrKey + 7);

	ParamFromDomMap ParamFromDom=LibDom->MapParamFromDom(XmlDomDoc,Vectorkey,"fieldset","field");

	vector<string> VectorFields, VectorValues;
	vector<string> WhereFields, WhereValues;

	for(unsigned i=0; i<ParamFromDom.size(); ++i){
		if (ParamFromDom[i]["name"]!="XaUser_ID" && ParamFromDom[i]["name"]!="tree_parent_ID") {
			string ParamValue=HTTP.GetHttpParam(ParamFromDom[i]["name"]);
			ParamValue=XaLibAction::HttpParamValidation(ParamFromDom[i]["name"],ParamValue,ParamFromDom[i]["datatype"],ParamFromDom[i]["required"],ParamFromDom[i]["dimension"],ParamFromDom[i]["domain"],ParamFromDom[i]["default"]);
	
			VectorFields.push_back(ParamFromDom[i]["dbname"]);
			VectorValues.push_back(ParamValue);
		}
	}

		VectorFields.push_back("active");
		VectorValues.push_back("1");

		VectorFields.push_back("deleted");
		VectorValues.push_back("0");

		// where
		string DecryptedXaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("XaUser_ID"));
		WhereFields.push_back("id");
		WhereValues.push_back(DecryptedXaUser_ID);

		XaLibSql* LibSql=new XaLibSql();
		int UpdateId=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues,WhereFields,WhereValues);
		delete (LibSql);

		if(UpdateId==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Department ID -> " + DecryptedXaUser_ID);

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Department ID -> "+ DecryptedXaUser_ID);

		}

	ParamFromDom.clear();
	VectorFields.clear();
	VectorValues.clear();

	// spostae messaggio di success/failure dentro if
	RESPONSE.Content="Department modified";
};


void XaUser::XaUserDepartmentView (){

    string LayoutType=HTTP.GetHttpParam("LayoutType");
    
    XaLibAction::AddXmlFile("XaUserDepartmentViewStruct");
    
    if(LayoutType=="Included"){
		XaLibAction::SetLayout("Included");
		XaLibAction::AddXslFile("XaUserDepartmentViewIncluded");
	} else {
		XaLibAction::SetLayout("ModalWindow");
		XaLibAction::AddXslFile("XaUserDepartmentView");
	}

	string XaUser_ID=XaLibAction::DecryptParamId(HTTP.GetHttpParam("RowId"));
	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserDepartmentViewData.xml");
	
	XaLibSql* LibSql=new XaLibSql();

	string QryDepartment="SELECT * FROM XaUser WHERE XaUserType_ID=2 AND id="+ XaUser_ID +" AND deleted=0";
	
	DbResMap DbResDepartment=LibSql->FreeQuery(DB_READ,QryDepartment);

		if (DbResDepartment.size()==1) {

			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserDepartmentView/data/department/";
			string ArrayXPathExpr[] = {XPB+"XaUser-Id",XPB+"XaUser-Surname",XPB+"XaUser-Company",XPB+"XaUser-Created",XPB+"XaUser-Last_Updated",XPB+"XaUser-Active"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+6);

			string ArrayXPathValue[] = {XaLibAction::EncryptParam(DbResDepartment[0]["id"]),DbResDepartment[0]["surname"],XaLibAction::SelectUserItem(DbResDepartment[0]["tree_parent_ID"]),DbResDepartment[0]["created"],DbResDepartment[0]["last_updated"],DbResDepartment[0]["active"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+6);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

			string ArrayXPathExprID[] = {"//XaUserDepartmentView/data/actions/action/id"};
			vector<string> XPathExprID(ArrayXPathExprID, ArrayXPathExprID+1);

			string ArrayXPathValueID[] = {XaLibAction::EncryptParam(DbResDepartment[0]["id"])};
			vector<string> XPathValueID(ArrayXPathValueID, ArrayXPathValueID+1);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp,XPathExprID,XPathValueID);
			
			XPathExprID.clear();
			XPathValueID.clear();

			XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocDataTemp));
		} else {
			//NOT UNIQUE
		}

	delete(LibSql);
	
		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		//LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,LibDom->StringFromDom(XmlDomDoc));
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"XaUser_ID",HTTP.GetHttpParam("RowId")};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserOrgChart (){

	XaLibAction::SetLayout("Standard");

	XaLibAction::AddXmlFile("XaUserOrgChart");
	XaLibAction::AddXslFile("XaUserOrgChart");

	
	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocTree=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserOrgChart.xml");

	XaLibSql* LibSql=new XaLibSql();


	string RowId=HTTP.GetHttpParam("RowId");
	string XaUser_ID;
	string QryOrg;
	int StartLevel;


// RowId (dipartimento) deve essere valorizzato per forza
// altrimenti parsa xml vuoto

if (RowId!="NoHttpParam") {

		XaUser_ID=XaLibAction::DecryptParamId(RowId);

		string QryPathRoot="SELECT tree_path FROM XaUser WHERE deleted=0 AND active=1 AND id="+XaUser_ID;
		DbResMap DbResPathRoot=LibSql->FreeQuery(DB_READ,QryPathRoot);
		string EmploymentPathRoot=DbResPathRoot[0]["tree_path"];

		QryOrg="SELECT id,name,surname,employment_parent_ID,employment_level,tree_parent_ID FROM XaUser WHERE deleted=0 AND active=1 AND employment_path LIKE '%" + EmploymentPathRoot+ "%' ";

		StartLevel=1;

		DbResMap DbResOrg=LibSql->FreeQuery(DB_READ,QryOrg);

		string QryMaxTreeLevel="SELECT max(employment_level) AS employment_level FROM XaUser WHERE deleted=0 AND active=1 AND employment_path LIKE '%" + EmploymentPathRoot+ "%' ";
		DbResMap DbResMaxTreeLevel=LibSql->FreeQuery(DB_READ,QryMaxTreeLevel);

		int MaxTreeLevel=XaLibBase::FromStringToInt(DbResMaxTreeLevel[0]["employment_level"]);

		string QryTreeRoot="SELECT surname FROM XaUser WHERE deleted=0 AND active=1 AND id=" + XaUser_ID;
		DbResMap DbResTreeRoot=LibSql->FreeQuery(DB_READ,QryTreeRoot);
		
		string TreeRootName=DbResTreeRoot[0]["surname"];

	//SERVE PER CAPIRE SE E' IL PRIMO GIRO
	int m=1;

	string XPathExpr0="//XaUserOrgChart";
	LibDom->AddOrgTreeOu(XmlDomDocTree, XPathExpr0,RowId,TreeRootName,"3");	//XaUserType_ID=3
	
	for (int i=StartLevel;i<=MaxTreeLevel;i++) {

		typedef map<int, map<string,string> > DbDataMap;
		DbDataMap DbData;

		int k=0;

		for (int j=0;j<DbResOrg.size();j++) {

			if (XaLibBase::FromStringToInt(DbResOrg[j]["employment_level"])==i) {

				DbData[k]["id"]=XaLibAction::EncryptParam(DbResOrg[j]["id"]);
				DbData[k]["employment_level"]=DbResOrg[j]["employment_level"];
				DbData[k]["name"]=DbResOrg[j]["name"];
				DbData[k]["surname"]=DbResOrg[j]["surname"];
				DbData[k]["employment_parent_ID"]=DbResOrg[j]["employment_parent_ID"];
				DbData[k]["department"]=XaLibAction::SelectUserItem(DbResOrg[j]["tree_parent_ID"]);

				string QryJobTitle="SELECT XaDomainJobTitle_ID FROM XaUserSalary WHERE XaTable='XaUser' AND deleted=0 AND active=1 AND XaField_ID="+DbResOrg[j]["id"];
				DbResMap DbResJobTitle=LibSql->FreeQuery(DB_READ,QryJobTitle);
				DbData[k]["jobtitle"]=XaLibAction::SelectDomainItem(DbResJobTitle[0]["XaDomainJobTitle_ID"]);

				string QryCheckLeaf="SELECT id FROM XaUser WHERE employment_parent_ID="+DbResOrg[j]["id"];
				DbResMap DbResCheckLeaf=LibSql->FreeQuery(DB_READ,QryCheckLeaf);
				if (DbResCheckLeaf.size()==0) {
					DbData[k]["employment_leaf"]="1";
				} else {
					DbData[k]["employment_leaf"]="0";
				}

				k++;

			} else {

			}

		}

		string XPathExpr="";

		for (int z=0;z<DbData.size();z++) {

			if (m==1) {

				XPathExpr="//ou[@id='"+RowId+"']";

			} else {

				XPathExpr="//user[@id='"+XaLibAction::EncryptParam(DbData[z]["employment_parent_ID"])+"']";
			}

			LibDom->AddOrgTreeUser(XmlDomDocTree, XPathExpr,DbData[z]["id"],DbData[z]["name"]+" "+DbData[z]["surname"],DbData[z]["department"],DbData[z]["jobtitle"]);

		}

		DbData.clear();
		m=0;
	}

	DbResOrg.clear();
	DbResMaxTreeLevel.clear();

		XaLibAction::AddXmlString(LibDom->StringFromDom(XmlDomDocTree));

}

		xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
		xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
		delete(LibDom);

const int MAXITEMS = 2;
string XslParams[MAXITEMS] = {"a","b"};
XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
RESPONSE.Content=LibXsl->GetXHtml();
delete(LibXsl);
};


void XaUser::XaUserOrgChartView (){

	XaLibAction::SetLayout("Standard");

	XaLibAction::AddXslFile("XaUserOrgChartView");
	XaLibAction::AddXmlFile("XaUserOrgChartViewFilter");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

	int RootId=1; // cerca company
	this->GetTreeChildren("XaUser",RootId,1,0);
	string XPathExprTreeParentID="/root/fieldset[@id='XaUserOrgChartView']/field[@name='tree_parent_ID']/options";
	XaLibAction::AddOptionsByVectors(LibDom,XmlDomDoc,XPathExprTreeParentID);

	delete(LibDom);

const int MAXITEMS = 2;
string XslParams[MAXITEMS] = {"a","b"};
XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
RESPONSE.Content=LibXsl->GetXHtml();
delete(LibXsl);
};


void XaUser::GetMyChildren(string TableName,string XPathExpr,int TreeStart) {

	DbResMap DbRes;
	DbResMap DbRes1;

	string StringTreeStart = XaLibBase::FromIntToString(TreeStart);

	XaLibSql* LibSql=new XaLibSql();
	//GETTING THE LEVEL
	DbRes=LibSql->SelectOne(DB_READ,"XaUser",TreeStart,1,0);

	int ParentLevel=XaLibBase::FromStringToInt(DbRes[0]["tree_level"])-1;

	string Qry="SELECT * FROM XaUser WHERE tree_level>="+XaLibBase::FromIntToString(ParentLevel)+" AND XaUserRole_ID=1  AND id>2 AND active=1 AND deleted=0 AND leaf=0 ORDER BY tree_path";
	DbRes1=LibSql->FreeQuery(DB_READ,Qry);
	delete(LibSql);


	for(unsigned n=0; n<DbRes1.size(); ++n){

		string spaces;
		
		for (int i=2;i<atoi(DbRes1[n]["tree_level"].c_str());i++ ){
		
			spaces.append("-");
		}

		XmlFields.push_back(spaces+DbRes1[n]["surname"]);
		XmlValues.push_back(XaLibAction::EncryptParam(DbRes1[n]["id"]));

	}

	DbRes.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options -> "+ TableName);
};


void XaUser::GetTreeChildren(string TableName,int TreeStart, int TreeLevels, int WithStart) {

	DbResMap DbRes;
	DbResMap DbRes1;
	map<string,string> ChildrenList;

	XaLibSql* LibSql=new XaLibSql();
	//GETTING THE LEVEL
	DbRes=LibSql->SelectOne(DB_READ, TableName, TreeStart, 1,0);
	string TreePathRoot=DbRes[0]["tree_path"];
	int StartLevel=XaLibBase::FromStringToInt(DbRes[0]["tree_level"]);
	int EndLevel=StartLevel+TreeLevels;
	if (WithStart==0) {StartLevel=StartLevel+1;};

	string Qry="SELECT id,surname,name FROM "+TableName+" WHERE tree_path LIKE '"+TreePathRoot+"%' AND tree_level BETWEEN "+XaLibBase::FromIntToString(StartLevel)+" AND "+XaLibBase::FromIntToString(EndLevel)+" AND active=1 AND deleted=0 ORDER BY surname";
	DbRes1=LibSql->FreeQuery(DB_READ,Qry);
	delete(LibSql);

	for(unsigned n=0; n<DbRes1.size(); ++n){
		XmlValues.push_back(XaLibAction::EncryptParam(DbRes1[n]["id"]));
		XmlFields.push_back(DbRes1[n]["surname"]+" "+DbRes1[n]["name"]);
	}

	DbRes.clear();
	DbRes1.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options -> "+ TableName);
};

void XaUser::GetAllLeaves(string TableName) {

	DbResMap DbRes;

	XaLibSql* LibSql=new XaLibSql();

	string Qry="SELECT id,surname,name FROM "+TableName+" WHERE leaf=1 AND active=1 AND deleted=0 ORDER BY surname";
	DbRes=LibSql->FreeQuery(DB_READ,Qry);
	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n){
		XmlValues.push_back(XaLibAction::EncryptParam(DbRes[n]["id"]));
		XmlFields.push_back(DbRes[n]["surname"]+" "+DbRes[n]["name"]);
	}

	DbRes.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options -> "+ TableName);
};


string XaUser::CalculateTreeLevel(string ParentTreeLevel) {
	
	int TreeLevel=XaLibBase::FromStringToInt(ParentTreeLevel)+1;
	
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated TreeLevel -> " + XaLibBase::FromIntToString(TreeLevel));

	return XaLibBase::FromIntToString(TreeLevel);
	
};

string XaUser::CalculateTreePath(string ParentTreePath,int NextId){
	
	string TreePath=ParentTreePath+ XaLibBase::FromIntToString(NextId) +"|";
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calculated TreePath -> "+ TreePath + " for User -> " + XaLibBase::FromIntToString(NextId));

	return TreePath;
};

void XaUser::UpdateTreeData(DbResMap DbResParent,int NextId){
	
	string StrArrFields[] = {"tree_level", "tree_path"};
	vector<string> VectorFields(StrArrFields, StrArrFields + 2);

	string StrArrValues[] = {this->CalculateTreeLevel(DbResParent[0]["tree_level"]),this->CalculateTreePath(DbResParent[0]["tree_path"],NextId)};
	vector<string> VectorValues(StrArrValues, StrArrValues + 2);

	vector<string> WhereFields;
	WhereFields.push_back("id");

	vector<string> WhereValues;
	WhereValues.push_back(XaLibBase::FromIntToString(NextId));

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating User -> " + XaLibBase::FromIntToString(NextId));
	
	XaLibSql* LibSql=new XaLibSql();

	int Status=LibSql->Update(DB_WRITE,"XaUser",VectorFields,VectorValues, WhereFields,WhereValues);
	delete (LibSql);
	if (Status==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Tree Data For User  -> " + XaLibBase::FromIntToString(NextId));

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Tree Data For User -> " + XaLibBase::FromIntToString(NextId));
//		this->ErrorExit("XaInfoPage","InsertDb");
	}
};

void XaUser::UpdateTreeData(int ParentId,int NextId){
		
	string StrArrReturnedFields[] = {"tree_level", "tree_path"};
	vector<string> ReturnedFields(StrArrReturnedFields, StrArrReturnedFields + 2);

	string StrArrWhereFields[] = {"id"};
	vector<string> WhereFields(StrArrWhereFields, StrArrWhereFields + 1);

	string StrArrWhereValues[] = {XaLibBase::FromIntToString(ParentId)};
	vector<string> WhereValues(StrArrWhereValues, StrArrWhereValues + 1);


	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbResParent=LibSql->Select(DB_READ,"XaUser",ReturnedFields,WhereFields,WhereValues);
	

	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	string StrArrUpdatingFields[] = {"tree_level", "tree_path"};
	vector<string> UpdatingFields(StrArrUpdatingFields, StrArrUpdatingFields + 2);
	
	string StrArrValues[] = {this->CalculateTreeLevel(DbResParent[0]["tree_level"]),this->CalculateTreePath(DbResParent[0]["tree_path"],NextId)};
	vector<string> VectorValues(StrArrValues, StrArrValues + 2);
	
	WhereFields.push_back("id");
	WhereValues.push_back(XaLibBase::FromIntToString(NextId));

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating Tree Data User -> " + XaLibBase::FromIntToString(NextId));

	int Status=LibSql->Update(DB_WRITE,"XaUser",UpdatingFields,VectorValues, WhereFields,WhereValues);
	delete (LibSql);

	if (Status==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated Tree Data For User  -> " + XaLibBase::FromIntToString(NextId));

	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating Tree Data For User -> " + XaLibBase::FromIntToString(NextId));

//		this->ErrorExit("XaInfoPage","InsertDb");
	}
};


void XaUser::SetOldId(int NextId){

	string StrNextId=XaLibBase::FromIntToString(NextId);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updating old_id for new User -> " + StrNextId);

	XaLibSql* LibSql=new XaLibSql();
	string QryLevel="UPDATE XaUser SET old_id=id WHERE id="+StrNextId;
	LibSql->FreeQueryNoRes(DB_READ,QryLevel);

};


void XaUser::XaUserXaUserProfileAdd(int XaUser_ID,int XaUserProfile_ID) {

	string StrArrFields[] = {"XaUser_ID","XaUserProfile_ID","active","deleted","created"};
	vector<string> VectorFields(StrArrFields, StrArrFields + 5);

	string StrArrValues[] = {XaLibBase::FromIntToString(XaUser_ID),XaLibBase::FromIntToString(XaUserProfile_ID), "1", "0",XaLibAction::NowTimeMysql};
	vector<string> VectorValues(StrArrValues, StrArrValues + 5);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Adding XaUserXaUserProfile Id -> " + XaLibBase::FromIntToString(XaUserProfile_ID) + " For User -> " + XaLibBase::FromIntToString(XaUser_ID));

	XaLibSql* LibSql=new XaLibSql();
	int NextId=LibSql->Insert(DB_WRITE,"XaUserXaUserProfile",VectorFields,VectorValues);
	delete (LibSql);

	if (NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Adding XaUserXaUserProfile Id -> " + XaLibBase::FromIntToString(XaUserProfile_ID) + " For User -> " + XaLibBase::FromIntToString(XaUser_ID));
//		this->ErrorExit("XaInfoPage","InsertDb");

	} else {

	}
};


void XaUser::XaUserRegistrationFrm (){
	
	string StrError=HTTP.GetHttpParam("error");
	
	XaLibAction::SetLayout("LoginFrm");
    XaLibAction::AddXmlFile("XaUserRegistrationFrm");
    XaLibAction::AddXslFile("XaUserRegistrationFrm");

	unique_ptr<XaLibDom> LibDom (new XaLibDom());
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);
    xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);

    string XslParams[2] = {"RegistrationError",StrError};
 
	unique_ptr<XaLibXsl> LibXsl (new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,2));
    RESPONSE.Content=LibXsl->GetXHtml();

};

void XaUser::XaUserRegistration (){

	string StrEmail=HTTP.GetHttpParam("email");
	string StrPassword1=HTTP.GetHttpParam("password1");
	string StrPassword2=HTTP.GetHttpParam("password2");

	if (StrEmail !="" && StrPassword1 !="" && StrPassword2 !="") {

		if (StrPassword1==StrPassword2) {

			XaLibCrypto* LibCrypto=new XaLibCrypto();
			string ShaPassword=LibCrypto->GetSha1(StrPassword1);
			delete (LibCrypto);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Email -> "+StrEmail);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Password -> "+ShaPassword);

			DbResMap DbRes;

			XaLibSql* LibSql=new XaLibSql();

			vector<string> ReturnedFields{"*"};
			vector<string> WhereFields{"email","deleted"};
			vector<string> WhereValues{StrEmail,"0"};

			DbRes=LibSql->Select(DB_SESSION,"XaUser",ReturnedFields,WhereFields,WhereValues);

			ReturnedFields.clear();
			WhereFields.clear();
			WhereValues.clear();

			int n=DbRes.size();

			if (n==1){

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"User Already Existing -> " + StrEmail);
				RESPONSE.Object="XaUser";
				RESPONSE.Event="XaUserRegistrationFrm";
				// error

			} else if (n==0){
				

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Registering User That Does Not Exist -> " + StrEmail);

				string StrTreeParentId="4";
				int IntTreeParentId=4;
				string StrXaUserTypeId="3";
				string StrXaUserRoleId="5";
				int IntXaUserProfileId=10;

				vector<string> VectorFields;
				vector<string> VectorValues;

				VectorFields.push_back("email");			VectorValues.push_back(StrEmail);
				VectorFields.push_back("password");			VectorValues.push_back(ShaPassword);
				VectorFields.push_back("tree_parent_ID");	VectorValues.push_back(StrTreeParentId);
				VectorFields.push_back("XaUserType_ID");	VectorValues.push_back(StrXaUserTypeId);
				VectorFields.push_back("XaUserRole_ID");	VectorValues.push_back(StrXaUserRoleId);
				VectorFields.push_back("leaf");				VectorValues.push_back("1");
				VectorFields.push_back("active");			VectorValues.push_back("1");
				VectorFields.push_back("deleted");			VectorValues.push_back("0");
				VectorFields.push_back("created");			VectorValues.push_back(XaLibAction::NowTimeMysql);
				// mancano deliberated e with_effect_from

				XaLibSql* LibSql=new XaLibSql();
				int NextId=LibSql->Insert(DB_WRITE,"XaUser",VectorFields,VectorValues);
				delete (LibSql);

				VectorFields.clear();
				VectorValues.clear();

				if(NextId==0) {

					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Registering User");
						//POST ACTION

				} else {

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"REgistered ID -> "+ XaLibBase::FromIntToString(NextId));

					this->UpdateTreeData(IntTreeParentId,NextId);
					this->XaUserXaUserProfileAdd(NextId,IntXaUserProfileId);
					this->SetOldId(NextId);

				}

				//UPDATE SESSION

				VectorFields.clear();
				VectorValues.clear();

				VectorFields.push_back("XaUser_ID");
				VectorValues.push_back(XaLibBase::FromIntToString(NextId));

				vector<string> VectorWhereFields{"SessionID"};
				vector<string> VectorWhereValues;
				VectorWhereValues.push_back(REQUEST.XaSession_ID);

				LibSql->Update(DB_SESSION,"XaSession",VectorFields,VectorValues,VectorWhereFields,VectorWhereValues);

				delete LibSql;

				RESPONSE.Object="XaPages";
				RESPONSE.Event="XaMyPage";

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"User Is Not Unique");
				//XaLibAction::PostAction="obj=XaInfoPage&evt=";
				RESPONSE.Object="XaInfoPage";
			
				///////////GESTIRE//////////
			}

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Passwords Do Not Match");
			RESPONSE.Object="XaUser";
			RESPONSE.Event="XaUserRegistrationFrm";
			// error=
		}

	} else {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Username Or Password Is Empty");
		RESPONSE.Object="XaUser";
		RESPONSE.Event="XaUserRegistrationFrm";
		// error=
	}

};


void XaUser::GetUsersAsOptions () {

	string tree_parent_ID=HTTP.GetHttpParam("tree_parent_ID");	//criptato
	string XaUserType_ID=HTTP.GetHttpParam("XaUserType_ID");

	string OptionsList="";
	OptionsList+="<option value=\"\">---</option>";

	XaLibSql* LibSql=new XaLibSql();

	if (XaUserType_ID!="" && tree_parent_ID!="") {

		string QryUsers="SELECT * FROM XaUser WHERE active=1 AND deleted=0";
		if (XaUserType_ID!="0" && XaUserType_ID!="NoHttpParam") {QryUsers+=" AND XaUserType_ID="+XaUserType_ID;};
		if (tree_parent_ID!="0" && tree_parent_ID!="NoHttpParam") {QryUsers+=" AND tree_parent_ID="+XaLibAction::DecryptParamId(tree_parent_ID);};
		QryUsers+= " ORDER BY surname";
		DbResMap DbResUsers=LibSql->FreeQuery(DB_READ,QryUsers);

		if (XaUserType_ID=="3") {OptionsList+="<option value=\""+XaLibAction::EncryptParam("0")+"\">Hierarchy Top User</option>";};

		for (int i=0;i<DbResUsers.size();i++) {
			// devo comporre una stringa invece di appendere nodi perche non ho un nodo root
			OptionsList+="<option value=\""+XaLibAction::EncryptParam(DbResUsers[i]["id"])+"\">";
			OptionsList+=DbResUsers[i]["surname"]+" "+DbResUsers[i]["name"];
			OptionsList+="</option>";
		}

	}

	delete(LibSql);

    RESPONSE.Content=OptionsList;

};


XaUser::DbResMap XaUser::GetUsersByMonth(string StrUserCondition,string StrTreeParentID,string StrCurrentMonth, string StrCurrentYear, string StrDeliberationId, string ReportType) {

		string MonthStart=StrCurrentYear+"-"+StrCurrentMonth+"-01";

		XaLibSql* LibSql=new XaLibSql();

		string Qry2="SELECT MAX(u2.XaUserSalaryDeliberation_ID) FROM XaUser u2 WHERE";
 		Qry2+=" u2.old_id IN (SELECT id FROM XaUser WHERE active=1 AND deleted=0) AND";
 		Qry2+=" u2.XaUserType_ID=3 AND u2.leaf=1";
 		Qry2+=" AND (u2.with_effect_from<='"+MonthStart+"' OR u2.with_effect_from IS NULL)";
 		if (StrDeliberationId!="") {
			Qry2+=" AND u2.XaUserSalaryDeliberation_ID<="+StrDeliberationId;
		}
 		if (ReportType=="actual") {
 			Qry2+=" AND vacant=0";
 		}
 		Qry2+=" AND u2.old_id = u1.old_id";

		string Qry1="SELECT u1.id,u1.old_id,u1.name,u1.middle_name,u1.surname,u1.tree_path,u1.tree_parent_id,u1.vacant FROM XaUser u1 WHERE";
		Qry1+=" u1.old_id IN (SELECT id FROM XaUser WHERE active=1 AND deleted=0) AND";
 		Qry1+=" u1.XaUserType_ID=3 AND u1.leaf=1";
  		if (StrDeliberationId!="") {
			Qry1+=" AND u1.XaUserSalaryDeliberation_ID<="+StrDeliberationId;
		}
 		Qry1+=" AND (u1.with_effect_from<='"+MonthStart+"' OR u1.with_effect_from IS NULL)";
 		Qry1+=" AND u1.XaUserSalaryDeliberation_ID=("+Qry2+")";
 		if (ReportType=="actual") {
 			Qry1+=" AND vacant=0";
 		}
 		if (StrTreeParentID!="0") {
			Qry1+=" AND u1.tree_path like '%|"+ StrTreeParentID +"|%'";
		} else { 
			Qry1+=" AND u1.tree_path like '|1|%'";
		}
		if (StrUserCondition!="") {
			Qry1+=StrUserCondition;
		}
		Qry1+=" GROUP BY u1.old_id";
		Qry1+=" ORDER BY u1.surname,u1.name";

		DbResMap DbResUserIds=LibSql->FreeQuery(DB_READ,Qry1);

		delete(LibSql);

		return DbResUserIds;
}

void XaUser::XaUserXaDomainAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserXaDomain");

    XaLibAction::AddXslFile("XaUserXaDomainTpl");
    XaLibAction::AddXslFile("XaUserXaDomainAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);

	string XPathExprType;

	XPathExprType="/root/fieldset[@id='XaUserXaDomain']/field[@name='XaUser-Section']/options";
	this->AddOptionsAllSection(LibDom,XmlDomDoc,XPathExprType);

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUser::XaUserXaDomainAdd () {

	string SectionId=HTTP.GetHttpParam("XaUser-Section");
	string JobTitle=HTTP.GetHttpParam("XaDomain-JobTitle-Right");
	vector<string> JobTitleArray=HTTP.GetHttpParamArray("XaDomain-JobTitle-Right");
	
	XaLibSql* LibSql=new XaLibSql();
	
	string ListXaUserXaDomainId="";
	string ListXaUserXaDomainIdSelected="";
	string ListXaUserXaDomainIdDel="";
	
	if (JobTitle!="NoHttpParam") {
	
		for(unsigned i=0; i<JobTitleArray.size(); ++i) {
			ListXaUserXaDomainIdSelected+=JobTitleArray[i]+",";
		}
		int ListXaUserXaDomainIdSelectedSize=ListXaUserXaDomainIdSelected.size()-1;
		ListXaUserXaDomainIdSelected=ListXaUserXaDomainIdSelected.substr (0,ListXaUserXaDomainIdSelectedSize);
		
		string QryDel="SELECT id FROM XaUserXaDomain WHERE XaUser_ID="+XaLibAction::DecryptParamId(SectionId)+" AND XaDomain_ID NOT IN("+ListXaUserXaDomainIdSelected+") AND active=1 AND deleted=0";
		DbResMap DbResDel=LibSql->FreeQuery(DB_READ,QryDel);
		
		for(unsigned t=0; t<DbResDel.size(); ++t) {
		
			vector<string> VectorFields, VectorValues, WhereFields, WhereValues;
	
			VectorFields.push_back("last_updated");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
	
			VectorFields.push_back("deleted");
			VectorValues.push_back("1");
	
			WhereFields.push_back("id");
			WhereValues.push_back(DbResDel[t]["id"]);
	
			LibSql->Update(DB_WRITE,"XaUserXaDomain",VectorFields,VectorValues,WhereFields,WhereValues);
			
			VectorFields.clear();
			VectorValues.clear();
			WhereFields.clear();
			WhereValues.clear();
			
			ListXaUserXaDomainIdDel+=DbResDel[t]["id"]+", ";
			
		}
		
		int ListXaUserXaDomainIdDelSize=ListXaUserXaDomainIdDel.size()-2;
		ListXaUserXaDomainIdDel=ListXaUserXaDomainIdDel.substr (0,ListXaUserXaDomainIdDelSize);
		
		for(unsigned n=0; n<JobTitleArray.size(); ++n) {
			
			string Qry="SELECT id FROM XaUserXaDomain WHERE XaUser_ID="+XaLibAction::DecryptParamId(SectionId)+" AND XaDomain_ID="+JobTitleArray[n]+" AND active=1 AND deleted=0";
			DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);
			
			// if there are no matches in the same table we insert
			if (DbRes.size()==0 && JobTitleArray[n]!="0") {
				vector<string> VectorFields, VectorValues;
				
				VectorFields.push_back("XaUser_ID");
				VectorValues.push_back(XaLibAction::DecryptParamId(SectionId));
			
				VectorFields.push_back("XaDomain_ID");
				VectorValues.push_back(JobTitleArray[n]);
		
				VectorFields.push_back("active");
				VectorValues.push_back("1");
		
				VectorFields.push_back("deleted");
				VectorValues.push_back("0");
		
				VectorFields.push_back("created");
				VectorValues.push_back(XaLibAction::NowTimeMysql);
				
				VectorFields.push_back("last_updated");
				VectorValues.push_back(XaLibAction::NowTimeMysql);
		
				int NextId=LibSql->Insert(DB_WRITE,"XaUserXaDomain",VectorFields,VectorValues);
				
				if(NextId==0) {
		
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserXaDomain");
		
				} else {
		
					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaUserXaDomain ID -> "+ XaLibBase::FromIntToString(NextId));
		
					ListXaUserXaDomainId+=XaLibBase::FromIntToString(NextId)+", ";
				}
		
				VectorFields.clear();
				VectorValues.clear();
			}
		
		}
		
		//delete (LibSql);
		
		int ListXaUserXaDomainIdSize=ListXaUserXaDomainId.size()-2;
		ListXaUserXaDomainId=ListXaUserXaDomainId.substr (0,ListXaUserXaDomainIdSize);

	} else if (JobTitle=="NoHttpParam") {
	
		string QryDel="SELECT id FROM XaUserXaDomain WHERE XaUser_ID="+XaLibAction::DecryptParamId(SectionId)+" AND active=1 AND deleted=0";
		DbResMap DbResDel=LibSql->FreeQuery(DB_READ,QryDel);
		
		for(unsigned t=0; t<DbResDel.size(); ++t) {
		
			vector<string> VectorFields, VectorValues, WhereFields, WhereValues;
	
			VectorFields.push_back("last_updated");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
	
			VectorFields.push_back("deleted");
			VectorValues.push_back("1");
	
			WhereFields.push_back("id");
			WhereValues.push_back(DbResDel[t]["id"]);
	
			LibSql->Update(DB_WRITE,"XaUserXaDomain",VectorFields,VectorValues,WhereFields,WhereValues);
			
			VectorFields.clear();
			VectorValues.clear();
			WhereFields.clear();
			WhereValues.clear();
			
			ListXaUserXaDomainIdDel+=DbResDel[t]["id"]+", ";
			
		}
		
		int ListXaUserXaDomainIdDelSize=ListXaUserXaDomainIdDel.size()-2;
		ListXaUserXaDomainIdDel=ListXaUserXaDomainIdDel.substr (0,ListXaUserXaDomainIdDelSize);
	
	}
	
	delete (LibSql);
	
	RESPONSE.Content="Inserted XaUserXaDomain -> ID: " + ListXaUserXaDomainId +" - Deleted XaUserXaDomain -> ID: " + ListXaUserXaDomainIdDel;
};

void XaUser::AddOptionsAllSection(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr){

	XaLibSql* LibSql=new XaLibSql();

	string Qry="SELECT id FROM XaUser WHERE tree_level=4 AND active=1 AND deleted=0";
	
	DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);
	
	delete(LibSql);

	for(unsigned n=0; n<DbRes.size(); ++n) {

		string OptionValue=XaLibAction::EncryptParam(DbRes[n]["id"]);
		string OptionLabel=this->ComposeXaUserBreadcrumb(DbRes[n]["id"]);

		LibDom->AddOptionElementByXPath(XmlDomDoc, XPathExpr,OptionLabel,OptionValue);
	}

	DbRes.clear();
	
};

void XaUser::XaUserGetXaDomainAsOptions () {

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");	//criptato
	string Domain=HTTP.GetHttpParam("domain");
	string XaUserXaDomainIn=HTTP.GetHttpParam("XaUserXaDomain-In");
	
	string OptionsList;

	XaLibSql* LibSql=new XaLibSql();

	if (Domain=="XaJobTitle") {

		string CondIn;
		if (XaUserXaDomainIn=="no") {
			CondIn=" NOT";
			OptionsList+="<option value=\"0\">---select items---</option>";
		} else if (XaUserXaDomainIn=="yes") {
			CondIn=" ";
			OptionsList+="<option value=\"0\">---selected items---</option>";
		}
		string Qry="SELECT id,name FROM XaDomain WHERE domain='XaJobTitle' AND active=1 AND deleted=0 AND id "+CondIn+" IN (SELECT XaDomain_ID FROM XaUserXaDomain WHERE XaUser_ID="+XaLibAction::DecryptParamId(XaUser_ID)+" AND active=1 AND deleted=0) ORDER BY name";
		
		DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

		for (int i=0;i<DbRes.size();i++) {
			
			OptionsList+="<option value=\""+DbRes[i]["id"]+"\">";
			OptionsList+=DbRes[i]["name"];
			OptionsList+="</option>";
		}
		
	}

	delete(LibSql);

    RESPONSE.Content=OptionsList;

};

void XaUser::XaUserCheckIfExist () {

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");	//criptato
	string Table=HTTP.GetHttpParam("table");
	string TableField=HTTP.GetHttpParam("table_field");
	string TableValue=HTTP.GetHttpParam("table_value");
	
	string Exist="Add";

	if (TableValue!="" && TableValue!="NoHttpParam") {
	
		XaLibSql* LibSql=new XaLibSql();
	
		string Qry;
		
		if (TableField=="email" && Table=="XaUser") {
			string QryMail="SELECT email FROM XaAddressMail WHERE id="+TableValue;
			DbResMap DbResMail=LibSql->FreeQuery(DB_READ,QryMail);
			
			Qry="SELECT id FROM " + Table + " WHERE "+ TableField +"='"+ DbResMail[0]["email"] + "' AND active=1 AND deleted=0";
		
		} else if (TableField=="XaField_ID" && Table=="XaUserSalary") {
			
			Qry="SELECT id FROM " + Table + " WHERE "+ TableField +"="+ XaLibAction::DecryptParamId(TableValue) + " AND active=1 AND deleted=0";
		
		} else if (TableField=="id" && Table=="XaUser") {
			
			Qry="SELECT email FROM " + Table + " WHERE "+ TableField +"="+ XaLibAction::DecryptParamId(TableValue) + " AND active IN (1,3) AND deleted=0 AND email !='' AND email IS NOT NULL";
		
		} else if (TableField=="password" && Table=="XaUser") {
			
			XaLibCrypto* LibCrypto=new XaLibCrypto();
			string ShaPassword=LibCrypto->GetSha1(TableValue);
			delete (LibCrypto);
			
			Qry="SELECT password FROM " + Table + " WHERE "+ TableField +"='"+ ShaPassword + "' AND id=" +XaLibAction::DecryptParamId(XaUser_ID)+ " AND active=1 AND deleted=0";
		
		}
		
			
		DbResMap DbRes=LibSql->FreeQuery(DB_SESSION,Qry);
	
		if (DbRes.size()>0) {
			
			Exist="Mod";
		
		}
		
		delete(LibSql);
	
	}

	RESPONSE.Content=Exist;

};

void XaUser::XaUserGetAllCompanyDepartmentSection() {

	XaLibSql* LibSql=new XaLibSql();
	
	string Qry1="SELECT id,surname FROM XaUser WHERE tree_level=2 AND XaUserType_ID=1 AND active=1 AND deleted=0 ORDER BY surname";
	DbResMap DbRes1=LibSql->FreeQuery(DB_READ,Qry1);

	for(unsigned n=0; n<DbRes1.size(); ++n){

		XmlFields.push_back(DbRes1[n]["surname"]);
		XmlValues.push_back(XaLibAction::EncryptParam(DbRes1[n]["id"]));
		
		string Qry2="SELECT id,surname FROM XaUser WHERE tree_level=3 AND XaUserType_ID=2 AND active=1 AND tree_parent_ID="+DbRes1[n]["id"]+" AND deleted=0 ORDER BY surname";
		DbResMap DbRes2=LibSql->FreeQuery(DB_READ,Qry2);
		
		for(unsigned i=0; i<DbRes2.size(); ++i){
			
			XmlFields.push_back("-"+DbRes2[i]["surname"]);
			XmlValues.push_back(XaLibAction::EncryptParam(DbRes2[i]["id"]));
			
			string Qry3="SELECT id,surname FROM XaUser WHERE tree_level=4 AND XaUserType_ID=2 AND active=1 AND tree_parent_ID="+DbRes2[i]["id"]+" AND deleted=0 ORDER BY surname";
			DbResMap DbRes3=LibSql->FreeQuery(DB_READ,Qry3);
		
			for(unsigned t=0; t<DbRes3.size(); ++t){
			
				XmlFields.push_back("--"+DbRes3[t]["surname"]);
				XmlValues.push_back(XaLibAction::EncryptParam(DbRes3[t]["id"]));
				
			}
			DbRes3.clear();
		}
		DbRes2.clear();

	}

	delete(LibSql);
	DbRes1.clear();

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added Options -> XaUser");
};
*/

void XaUserUi::List () {

	AddJsVarFile("XaModel","XaUser");
	AddJsVarString("XaGuiStyle","default");

	/* data */

	vector <string> FieldsValues ={};

	FieldsValues.push_back(HTTP.GetHttpParam("tree_parent_ID"));
	
	XaLibCurl LibCurl;
    string CallResponse = LibCurl.Call(BuildBackEndCall("XaUser","List",{"tree_parent_ID"},{FieldsValues}));
	CheckResponse(CallResponse);

	AddJsVarString("XaData",CallResponse);

	/* end of data */

	vector<string> Templates=SetPageLayout(REQUEST.CalledLayout);
	Templates.push_back("XaGuiUserList");

	RESPONSE.Content=XaLibDom::HtmlFromStringAndFile(AddHtmlFiles(Templates),HtmlStrings,JsVarFiles,JsVarStrings,0);
};

XaUserUi::~XaUserUi(){
};