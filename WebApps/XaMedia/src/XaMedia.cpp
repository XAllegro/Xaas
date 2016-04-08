#include <XaMedia.h>
#include <XaLibModel.h>

XaMedia::XaMedia() {
};

void XaMedia::Dispatcher(const string &CalledEvent) {
	
    if (CalledEvent=="GetXmlModel"){
        this->GetXmlModel();
    }else if (CalledEvent=="List"){
        this->List();
    }else if (CalledEvent=="Read"){
        this->Read();
    }else if (CalledEvent=="Create"){
        this->Create();
    }else if (CalledEvent=="Update"){
	this->Update();
    }else if (CalledEvent=="ReadForUpdateFrm"){
	this->ReadForUpdateFrm();
    }else if (CalledEvent=="Delete"){
	this->Delete();
    }else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }

};

void XaMedia::List(){
    
	string XaField_ID=HTTP.GetHttpParam("XaField_ID");
        string XaTable=HTTP.GetHttpParam("XaTable");

	string XPathExpr="/XaMedia/fieldset/field";
	vector<string> XmlFiles = {"XaMedia"};


	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	string QryFields="SELECT R.id";
	string QryJoin="";

	for (auto i=0;i<FieldsNum;i++) {

		string j=to_string(i+1);

		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/list")=="yes") {

			if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="select-single-domain") {
				string FieldName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
				QryFields+=",X"+j+".name AS "+FieldName;
				QryJoin+=" LEFT JOIN XaDomain X"+j+" ON X"+j+".id=R."+FieldName;
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="input-text"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="input-number"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="select-boolean"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="external-key"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			}
			
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field to retrieve for the list ->"+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};

	};

	QryFields+=" FROM XaMedia R";

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Fields ->"+QryFields);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Join ->"+QryJoin);
	
	string Qry=QryFields+QryJoin;
	Qry+=" WHERE R.status=1 AND R.XaField_ID="+XaField_ID+" AND R.XaTable='"+XaTable+"'";

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query ->"+Qry);

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	vector<string> ListFields=ListPrepare({"XaMedia"},"/XaMedia/fieldset/field",0);

	RESPONSE.Content=ListResponse(DbRes,ListFields);
};

void XaMedia::Read(){

	string Id=HTTP.GetHttpParam("id");

	string XPathExpr="/XaMedia/fieldset/field";
	vector<string> XmlFiles = {"XaMedia"};


	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	string QryFields="SELECT R.id";
	string QryJoin="";

	for (auto i=0;i<FieldsNum;i++) {

		string j=to_string(i+1);

		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/read")=="yes") {

			if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="select-single-domain") {
				string FieldName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
				QryFields+=",X"+j+".name AS "+FieldName;
				QryJoin+=" LEFT JOIN XaDomain X"+j+" ON X"+j+".id=R."+FieldName;
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="input-text"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="input-number"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="select-boolean"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			} else if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/type")=="external-key"){
				QryFields+=",R."+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+j+"]/name");
			}
			
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field to retrieve for the list ->"+XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};

	};

	QryFields+=" FROM XaMedia R";

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Fields ->"+QryFields);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Join ->"+QryJoin);
	
	string Qry=QryFields+QryJoin;
	Qry+=" WHERE R.id="+Id;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query ->"+Qry);

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	vector<string> ReadFields=ReadPrepare({"XaMedia"},"/XaMedia/fieldset/field",0);

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaMedia::Create(){

    vector<string> FieldName;	
    vector<string> FieldValue;

    //FieldName.push_back("RpRe_ID");
    //FieldValue.push_back(HTTP.GetHttpParam("XaMedia-RpRe_ID"));

    CreatePrepare({"XaMedia"},"/XaMedia/fieldset/field",FieldName,FieldValue);
    CreateExecute("XaMedia",FieldName,FieldValue);
}

void XaMedia::Update(){

    string Id=HTTP.GetHttpParam("id");
    int UpdateId=XaLibBase::FromStringToInt(Id);
    
    vector<string> FieldName;	
    vector<string> FieldValue;
    
    UpdatePrepare({"XaMedia"},"/XaMedia/fieldset/field",FieldName,FieldValue);

    int Updated=UpdateExecute("XaMedia",FieldName,FieldValue,UpdateId);
	
	RESPONSE.Content=UpdateResponse(Updated);
};

void XaMedia::ReadForUpdateFrm() {

    string Id=HTTP.GetHttpParam("id");

    vector<string> ReadFields=ReadPrepare({"XaMedia"},"/XaMedia/fieldset/field",0);

    DbResMap DbRes=XaLibSql::Select(DB_READ,"XaMedia",{ReadFields},{"id"},{Id});

    RESPONSE.Content=ReadResponse(DbRes,ReadFields);

};

void XaMedia::Delete(){

    int DeletedId = DeleteExecute("XaMedia",HTTP.GetHttpParam("id"));
    RESPONSE.Content = DeleteResponse(DeletedId);
};

XaMedia::~XaMedia(){
};