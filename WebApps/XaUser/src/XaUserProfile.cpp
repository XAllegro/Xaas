#include <XaUserProfile.h>

#include <XaLibAction.h>

using namespace std;

XaUserProfile::XaUserProfile(){
};

void XaUserProfile::Dispatcher (const string& CalledEvent) {
	
	if (CalledEvent=="XaUserProfileXaUserActionAddFrm"){

        this->XaUserProfileXaUserActionAddFrm();

    } else if (CalledEvent=="XaUserProfileXaUserActionAdd"){

        this->XaUserProfileXaUserActionAdd();

    } else if (CalledEvent=="XaUserProfileGetXaUserActionAsOptions"){

        this->XaUserProfileGetXaUserActionAsOptions();

    } else if (CalledEvent=="XaUserProfileAddFrm"){

        this->XaUserProfileAddFrm();

    } else if (CalledEvent=="XaUserProfileAdd"){

        this->XaUserProfileAdd();

    } else if (CalledEvent=="XaUserProfileMod"){

        this->XaUserProfileMod();

    } else if (CalledEvent=="XaUserProfileList"){

        this->XaUserProfileList();

    } else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
	}

};

void XaUserProfile::XaUserProfileAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserProfile");

    XaLibAction::AddXslFile("XaUserProfileTpl");
    XaLibAction::AddXslFile("XaUserProfileAddFrm");

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

void XaUserProfile::XaUserProfileAdd (){

    string Name=HTTP.GetHttpParam("XaUserProfile-Name");
	string StrDescription=HTTP.GetHttpParam("XaUserProfile-Description");
	
	XaLibChar* LibChar=new XaLibChar;
	string StrName=LibChar->RemoveEmptyspace(Name);
	delete (LibChar);
	
	vector<string> ReturnedFields, WhereFields, WhereValues;
	ReturnedFields.push_back("id");
	WhereFields.push_back("name");
	WhereValues.push_back(StrName);
	WhereFields.push_back("active");
	WhereValues.push_back("1");
	WhereFields.push_back("deleted");
	WhereValues.push_back("0");

	XaLibSql* LibSql=new XaLibSql();
	DbResMap DbRes=LibSql->Select(DB_READ,"XaUserProfile",ReturnedFields,WhereFields,WhereValues);
	
	ReturnedFields.clear();
	WhereFields.clear();
	WhereValues.clear();
	
	string Res;
	if (DbRes.size()==0){
	
		vector<string> VectorFields, VectorValues;
	
		VectorFields.push_back("name");
		VectorValues.push_back(StrName);
		
		VectorFields.push_back("description");
		VectorValues.push_back(StrDescription);
		
		VectorFields.push_back("active");
		VectorValues.push_back("1");
	
		VectorFields.push_back("deleted");
		VectorValues.push_back("0");
	
		VectorFields.push_back("created");
		VectorValues.push_back(XaLibAction::NowTimeMysql);
		
		VectorFields.push_back("last_updated");
		VectorValues.push_back(XaLibAction::NowTimeMysql);
		
		int NextId=LibSql->Insert(DB_WRITE,"XaUserProfile",VectorFields,VectorValues);
			
		if(NextId==0) {
			
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserProfile");
			Res="Error Inserting User Profile";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaUserProfile ID -> "+ XaLibBase::FromIntToString(NextId));
			Res="User Profile Successfully Added";
		
		}
		
		VectorFields.clear();
		VectorValues.clear();
	
	}else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserProfile");
		Res="Error: User Profile Already Exists";
		
	}
	
	delete (LibSql);
	RESPONSE.Content=Res;
	//XHtmlPage=Res;

};

void XaUserProfile::XaUserProfileMod(){

	string XaUserProfile_ID=HTTP.GetHttpParam("XaUserProfile_ID");
	string Active=HTTP.GetHttpParam("XaUserProfile-Active");
	
	XaLibSql* LibSql=new XaLibSql();

	// MOD Login
	vector<string> VectorFields, VectorValues, WhereFields, WhereValues;

	VectorFields.push_back("active");
	VectorValues.push_back(Active);
	
	VectorFields.push_back("last_updated");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	WhereFields.push_back("id");
	WhereValues.push_back(XaUserProfile_ID);
		
	int UpdateId=LibSql->Update(DB_WRITE,"XaUserProfile",VectorFields,VectorValues,WhereFields,WhereValues);
	
	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
	
		string Res;
		
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating XaUserProfile - Mod field active ID -> "+XaUserProfile_ID);
			Res="error modifying user profile";
			
		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated XaUserProfile - Mod field active ID -> "+XaUserProfile_ID);
			Res="user profile successfully modified";
	
		}
	
	//XHtmlPage=Res;
	RESPONSE.Content=Res;

};

void XaUserProfile::XaUserProfileList (){
	
	XaLibAction::SetLayout("Standard");
    XaLibAction::AddXslFile("XaUserProfileList");

    XaLibAction::AddXmlFile("XaUserProfileListStruct");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserProfileListData.xml");

	XaLibSql* LibSql=new XaLibSql();

	string QryUser="SELECT id,name,description,active FROM XaUserProfile WHERE deleted=0 AND id > 2";
	
	DbResMap DbResUser=LibSql->FreeQuery(DB_READ,QryUser);

		for (int i=0;i<DbResUser.size();i++) {
			
			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserProfileList/data/profile/";
			string ArrayXPathExpr[] = {XPB+"XaUserProfile-Id",XPB+"XaUserProfile-Active",XPB+"XaUserProfile-Name",XPB+"XaUserProfile-Description"};
			vector<string> XPathExpr(ArrayXPathExpr, ArrayXPathExpr+4);

			string ArrayXPathValue[] = {DbResUser[i]["id"],DbResUser[i]["active"],DbResUser[i]["name"],DbResUser[i]["description"]};
			vector<string> XPathValue(ArrayXPathValue, ArrayXPathValue+4);

			LibDom->UpdateElementValueByXPath(XmlDomDocDataTemp, XPathExpr, XPathValue);

			XPathExpr.clear();
			XPathValue.clear();

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

void XaUserProfile::XaUserProfileXaUserActionAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserProfileXaUserAction");

    XaLibAction::AddXslFile("XaUserProfileXaUserActionTpl");
    XaLibAction::AddXslFile("XaUserProfileXaUserActionAddFrm");

    XaLibDom* LibDom=new XaLibDom();
    xmlDocPtr XmlDomDoc=LibDom->DomFromStringAndFile(XmlFiles,XmlStrings,1);

	string XPathExprType;

	XPathExprType="/root/fieldset[@id='XaUserProfileXaUserAction']/field[@name='XaUserProfile']/options";
	XaLibAction::AddOptionsByDbWithCondition(LibDom,XmlDomDoc,"XaUserProfile",XPathExprType," AND id>2");

	xmlDocPtr XslDomDoc=LibDom->DomFromStringAndFile(XslFiles,XslStrings,2);
	delete(LibDom);

    const int MAXITEMS = 2;
    string XslParams[MAXITEMS] = {"a","b"};
    XaLibXsl *LibXsl=new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams,MAXITEMS);
    RESPONSE.Content=LibXsl->GetXHtml();
	delete(LibXsl);

};

void XaUserProfile::XaUserProfileXaUserActionAdd () {

	string XaUserProfile_ID=HTTP.GetHttpParam("XaUserProfile");
	string XaUserAction=HTTP.GetHttpParam("XaUserAction-Right");
	vector<string> XaUserActionArray=HTTP.GetHttpParamArray("XaUserAction-Right");
	
	XaLibSql* LibSql=new XaLibSql();
	
	string ListXaUserActionId="";
	string ListXaUserActionIdSelected="";
	string ListXaUserActionIdDel="";
	
	if (XaUserAction!="NoHttpParam") {
	
		for(unsigned i=0; i<XaUserActionArray.size(); ++i) {
			ListXaUserActionIdSelected+=XaUserActionArray[i]+",";
		}
		int ListXaUserActionIdSelectedSize=ListXaUserActionIdSelected.size()-1;
		ListXaUserActionIdSelected=ListXaUserActionIdSelected.substr (0,ListXaUserActionIdSelectedSize);
		
		string QryDel="SELECT id FROM XaUserProfileXaUserAction WHERE XaUserProfile_ID="+ XaUserProfile_ID +" AND XaUserAction_ID NOT IN("+ListXaUserActionIdSelected+") AND active=1 AND deleted=0";
		DbResMap DbResDel=LibSql->FreeQuery(DB_READ,QryDel);
		
		for(unsigned t=0; t<DbResDel.size(); ++t) {
		
			vector<string> VectorFields, VectorValues, WhereFields, WhereValues;
	
			VectorFields.push_back("last_updated");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
	
			VectorFields.push_back("deleted");
			VectorValues.push_back("1");
	
			WhereFields.push_back("id");
			WhereValues.push_back(DbResDel[t]["id"]);
	
			LibSql->Update(DB_WRITE,"XaUserProfileXaUserAction",VectorFields,VectorValues,WhereFields,WhereValues);
			
			VectorFields.clear();
			VectorValues.clear();
			WhereFields.clear();
			WhereValues.clear();
			
			ListXaUserActionIdDel+=DbResDel[t]["id"]+", ";
			
		}
		
		int ListXaUserActionIdDelSize=ListXaUserActionIdDel.size()-2;
		ListXaUserActionIdDel=ListXaUserActionIdDel.substr (0,ListXaUserActionIdDelSize);
		
		for(unsigned n=0; n<XaUserActionArray.size(); ++n) {
			
			string Qry="SELECT id FROM XaUserProfileXaUserAction WHERE XaUserProfile_ID="+ XaUserProfile_ID +" AND XaUserAction_ID="+XaUserActionArray[n]+" AND active=1 AND deleted=0";
			DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);
			
			// if there are no matches in the same table we insert
			if (DbRes.size()==0 && XaUserActionArray[n]!="0") {
				vector<string> VectorFields, VectorValues;
				
				VectorFields.push_back("XaUserProfile_ID");
				VectorValues.push_back(XaUserProfile_ID);
			
				VectorFields.push_back("XaUserAction_ID");
				VectorValues.push_back(XaUserActionArray[n]);
		
				VectorFields.push_back("active");
				VectorValues.push_back("1");
		
				VectorFields.push_back("deleted");
				VectorValues.push_back("0");
		
				VectorFields.push_back("created");
				VectorValues.push_back(XaLibAction::NowTimeMysql);
				
				VectorFields.push_back("last_updated");
				VectorValues.push_back(XaLibAction::NowTimeMysql);
		
				int NextId=LibSql->Insert(DB_WRITE,"XaUserProfileXaUserAction",VectorFields,VectorValues);
				
				if(NextId==0) {
		
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserProfileXaUserAction");
		
				} else {
		
					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaUserProfileXaUserAction ID -> "+ XaLibBase::FromIntToString(NextId));
		
					ListXaUserActionId+=XaLibBase::FromIntToString(NextId)+", ";
				}
		
				VectorFields.clear();
				VectorValues.clear();
			}
		
		}
		
		//delete (LibSql);
		
		int ListXaUserActionIdSize=ListXaUserActionId.size()-2;
		ListXaUserActionId=ListXaUserActionId.substr (0,ListXaUserActionIdSize);

	} else if (XaUserAction=="NoHttpParam") {
	
		string QryDel="SELECT id FROM XaUserProfileXaUserAction WHERE XaUserProfile_ID="+ XaUserProfile_ID +" AND active=1 AND deleted=0";
		DbResMap DbResDel=LibSql->FreeQuery(DB_READ,QryDel);
		
		for(unsigned t=0; t<DbResDel.size(); ++t) {
		
			vector<string> VectorFields, VectorValues, WhereFields, WhereValues;
	
			VectorFields.push_back("last_updated");
			VectorValues.push_back(XaLibAction::NowTimeMysql);
	
			VectorFields.push_back("deleted");
			VectorValues.push_back("1");
	
			WhereFields.push_back("id");
			WhereValues.push_back(DbResDel[t]["id"]);
	
			LibSql->Update(DB_WRITE,"XaUserProfileXaUserAction",VectorFields,VectorValues,WhereFields,WhereValues);
			
			VectorFields.clear();
			VectorValues.clear();
			WhereFields.clear();
			WhereValues.clear();
			
			ListXaUserActionIdDel+=DbResDel[t]["id"]+", ";
			
		}
		
		int ListXaUserActionIdDelSize=ListXaUserActionIdDel.size()-2;
		ListXaUserActionIdDel=ListXaUserActionIdDel.substr (0,ListXaUserActionIdDelSize);
	
	}
	
	delete (LibSql);
	
	RESPONSE.Content="Inserted XaUserProfileXaUserAction -> ID: " + ListXaUserActionId +" - Deleted XaUserProfileXaUserAction -> ID: " + ListXaUserActionIdDel;
};

void XaUserProfile::XaUserProfileGetXaUserActionAsOptions () {

	string XaUserProfile_ID=HTTP.GetHttpParam("XaUserProfile_ID");	//criptato
	//string Domain=HTTP.GetHttpParam("domain");
	string TableIn=HTTP.GetHttpParam("Table-In");
	
	string OptionsList;
	//OptionsList+="<option value=0\"\">---</option>";

	XaLibSql* LibSql=new XaLibSql();

		string CondIn;
		if (TableIn=="no") {
			CondIn=" NOT";
			OptionsList+="<option value=\"0\">---select items---</option>";
		} else if (TableIn=="yes") {
			CondIn=" ";
			OptionsList+="<option value=\"0\">---selected items---</option>";
		}
		string Qry="SELECT id,description FROM XaUserAction WHERE active=1 AND deleted=0 AND id "+CondIn+" IN (SELECT XaUserAction_ID FROM XaUserProfileXaUserAction WHERE XaUserProfile_ID="+ XaUserProfile_ID +" AND active=1 AND deleted=0) ORDER BY description";
		
		DbResMap DbRes=LibSql->FreeQuery(DB_READ,Qry);

		for (int i=0;i<DbRes.size();i++) {
			
			OptionsList+="<option value=\""+DbRes[i]["id"]+"\">";
			OptionsList+=DbRes[i]["description"];
			OptionsList+="</option>";
		}

	delete(LibSql);

	RESPONSE.Content=OptionsList;

};

int XaUserProfile::EventIsFree(const string& CalledObject, const string& CalledEvent) {

	int ReturnStatus=0;
	XaLibSql LibSql;

	string QryAction="SELECT free,active,deleted FROM XaUserAction WHERE object =\""+CalledObject+"\" AND event=\""+CalledEvent+"\"";
	DbResMap DbResAction=LibSql.FreeQuery(DB_SESSION,QryAction);

	if (DbResAction.size()==1) {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Unique -> "+CalledObject+"::"+CalledEvent);

		if (XaLibBase::FromStringToInt(DbResAction[0]["deleted"])==0){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Deleted -> "+CalledObject+"::"+CalledEvent);

			if (XaLibBase::FromStringToInt(DbResAction[0]["active"])==1){

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Active -> "+CalledObject+"::"+CalledEvent);

				if (XaLibBase::FromStringToInt(DbResAction[0]["free"])==1){

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Free -> "+CalledObject+"::"+CalledEvent);

					ReturnStatus=1;

				} else {

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Free -> "+CalledObject+"::"+CalledEvent);
				}

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Active -> "+CalledObject+"::"+CalledEvent);

			}

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Deleted -> "+CalledObject+"::"+CalledEvent);

		}

	} else if (DbResAction.size()>1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Unique -> "+CalledObject+"::"+CalledEvent);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Does NOT Exist -> "+CalledObject+"::"+CalledEvent);
	}

	DbResAction.clear();

	return ReturnStatus;

};

int XaUserProfile::EventProfile(const string& CalledObject, const string& CalledEvent) {

	int ReturnStatus=0;

	string QryAction="SELECT XaUserAction.object AS object,XaUserAction.event AS event,XaUserAction.active AS active,XaUserAction.deleted AS deleted "
	"FROM XaUserXaUserProfile,XaUserProfile,XaUserProfileXaUserAction,XaUserAction "
	"WHERE 1=1 "
	//"WHERE XaUserAction.active=1 AND XaUserAction.deleted=0"
	"AND XaUserXaUserProfile.active=1 AND XaUserProfile.active=1 AND XaUserProfileXaUserAction.active=1 AND XaUserAction.active=1 "
	"AND XaUserXaUserProfile.deleted=0 AND XaUserProfile.deleted=0 AND XaUserProfileXaUserAction.deleted=0 AND XaUserAction.deleted=0 "
	"AND XaUserAction.object=\""+CalledObject+"\" AND event=\""+CalledEvent+"\" " 
	"AND XaUserXaUserProfile.XaUser_ID="+ XaLibBase::FromIntToString(REQUEST.XaUser_ID)+" "
	"AND XaUserXaUserProfile.XaUserProfile_ID=XaUserProfile.id "
	"AND XaUserProfileXaUserAction.XaUserProfile_ID=XaUserProfile.id "
	"AND XaUserProfileXaUserAction.XaUserAction_ID=XaUserAction.id";

	XaLibSql LibSql;
	DbResMap DbResAction=LibSql.FreeQuery(DB_SESSION,QryAction);

	if (DbResAction.size()==1) {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Unique -> "+CalledObject+"::"+CalledEvent);

		if (XaLibBase::FromStringToInt(DbResAction[0]["deleted"])==0){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Deleted -> "+CalledObject+"::"+CalledEvent);

			if (XaLibBase::FromStringToInt(DbResAction[0]["active"])==1){

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Active -> "+CalledObject+"::"+CalledEvent);
				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Profiled Object-Event -> "+CalledObject+"::"+CalledEvent);
				ReturnStatus=1;

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT Active -> "+CalledObject+"::"+CalledEvent);
			}

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is Deleted -> "+CalledObject+"::"+CalledEvent);
		}

	} else {
		//LOPPA
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Object-Event Is NOT In Profile -> "+CalledObject+"::"+CalledEvent);
		ErrorExit("EventNotProfiled");
	}

	DbResAction.clear();
	return ReturnStatus;
};

XaUserProfile::~XaUserProfile(){
};