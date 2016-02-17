#include <XaUserRole.h>
#include <XaLibAction.h>


XaUserRole::XaUserRole(){
};

void XaUserRole::Dispatcher (const string &CalledEvent) {
	
	if (CalledEvent=="XaUserRoleAddFrm"){

        this->XaUserRoleAddFrm();

    } else if (CalledEvent=="XaUserRoleAdd"){

        this->XaUserRoleAdd();

    } else if (CalledEvent=="XaUserRoleMod"){

        this->XaUserRoleMod();

    } else if (CalledEvent=="XaUserRoleList"){

        this->XaUserRoleList();

    } else {
	
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Event Does Not Exists -> "+CalledEvent);
	}

};

void XaUserRole::XaUserRoleAddFrm (){

    XaLibAction::SetLayout("Standard");

    XaLibAction::AddXmlFile("XaUserRole");

    XaLibAction::AddXslFile("XaUserRoleTpl");
    XaLibAction::AddXslFile("XaUserRoleAddFrm");

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

void XaUserRole::XaUserRoleAdd (){

    string Name=HTTP.GetHttpParam("XaUserRole-Name");
	string StrDescription=HTTP.GetHttpParam("XaUserRole-Description");
	
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
	DbResMap DbRes=LibSql->Select(DB_READ,"XaUserRole",ReturnedFields,WhereFields,WhereValues);
	
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
		
		int NextId=LibSql->Insert(DB_WRITE,"XaUserRole",VectorFields,VectorValues);
			
		if(NextId==0) {
			
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserRole");
			Res="Error Inserting User Role";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted XaUserRole ID -> "+ XaLibBase::FromIntToString(NextId));
			Res="User Role Successfully Added";
		
		}
		
		VectorFields.clear();
		VectorValues.clear();
	
	}else {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Inserting XaUserRole");
			Res="Error: User Role Already Exists";
		
	}
	
	delete (LibSql);
	
	RESPONSE.Content=Res;

};

void XaUserRole::XaUserRoleMod(){

	string XaUserRole_ID=HTTP.GetHttpParam("XaUserRole_ID");
	string Active=HTTP.GetHttpParam("XaUserRole-Active");
	
	XaLibSql* LibSql=new XaLibSql();
		
	// MOD Login
	vector<string> VectorFields, VectorValues, WhereFields, WhereValues;

	VectorFields.push_back("active");
	VectorValues.push_back(Active);
	
	VectorFields.push_back("last_updated");
	VectorValues.push_back(XaLibAction::NowTimeMysql);

	WhereFields.push_back("id");
	WhereValues.push_back(XaUserRole_ID);
		
	int UpdateId=LibSql->Update(DB_WRITE,"XaUserRole",VectorFields,VectorValues,WhereFields,WhereValues);
	
	VectorFields.clear();
	VectorValues.clear();
	WhereFields.clear();
	WhereValues.clear();
	
		string Res;
		
		if(UpdateId==0) {
	
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Updating XaUserRole - Mod field active ID -> "+XaUserRole_ID);
			Res="error modifying user role";
			
		} else {
	
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated XaUserRole - Mod field active ID -> "+XaUserRole_ID);
			Res="user role successfully modified";
	
		}
	
	RESPONSE.Content=Res;

};

void XaUserRole::XaUserRoleList (){

	//string Login=HTTP.GetHttpParam("XaUser-Login");
	
	XaLibAction::SetLayout("Standard");
    XaLibAction::AddXslFile("XaUserRoleList");

    XaLibAction::AddXmlFile("XaUserRoleListStruct");

	XaLibDom* LibDom=new XaLibDom();
	xmlDocPtr XmlDomDocData=LibDom->DomFromFile(SETTINGS["XmlDir"]+"XaUserRoleListData.xml");

	XaLibSql* LibSql=new XaLibSql();

	string QryUser="SELECT id,name,description,active FROM XaUserRole WHERE deleted=0 AND id > 2";
	
	DbResMap DbResUser=LibSql->FreeQuerySelect(DB_READ,QryUser);

		for (int i=0;i<DbResUser.size();i++) {
			
			xmlDocPtr XmlDomDocDataTemp=xmlCopyDoc(XmlDomDocData,1);
			
			string XPB="//XaUserRoleList/data/role/";
			string ArrayXPathExpr[] = {XPB+"XaUserRole-Id",XPB+"XaUserRole-Active",XPB+"XaUserRole-Name",XPB+"XaUserRole-Description"};
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

XaUserRole::~XaUserRole(){
};
