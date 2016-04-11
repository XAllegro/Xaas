#include <XaMediaData.h>
#include <XaLibModel.h>
#include <XaLibTime.h>

XaMediaData::XaMediaData() {
};

void XaMediaData::Dispatcher(const string &CalledEvent) {
	
    if (CalledEvent=="GetXmlModel"){
        this->GetXmlModel();
    }else if (CalledEvent=="List"){
        this->List();
    }else if (CalledEvent=="Read"){
        this->Read();
    }else if (CalledEvent=="Create"){
        this->Create();
    }else if (CalledEvent=="Delete"){
	this->Delete();
    }else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }

};

void XaMediaData::List(){
    
	string XaMedia_ID=HTTP.GetHttpParam("XaMedia_ID");

	string XPathExpr="/XaMediaData/fieldset/field";
	vector<string> XmlFiles = {"XaMediaData"};


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

	QryFields+=" FROM XaMediaData R";

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Fields ->"+QryFields);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Join ->"+QryJoin);
	
	string Qry=QryFields+QryJoin;
	Qry+=" WHERE R.status=1 AND R.XaMedia_ID="+XaMedia_ID;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query ->"+Qry);

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	vector<string> ListFields=ListPrepare({"XaMediaData"},"/XaMediaData/fieldset/field",0);

	RESPONSE.Content=ListResponse(DbRes,ListFields);
};

void XaMediaData::Read(){

	string Id=HTTP.GetHttpParam("id");

	string XPathExpr="/XaMediaData/fieldset/field";
	vector<string> XmlFiles = {"XaMediaData"};


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

	QryFields+=" FROM XaMediaData R";

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Fields ->"+QryFields);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Join ->"+QryJoin);
	
	string Qry=QryFields+QryJoin;
	Qry+=" WHERE R.id="+Id;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query ->"+Qry);

    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	vector<string> ReadFields=ReadPrepare({"XaMediaData"},"/XaMediaData/fieldset/field",0);

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaMediaData::Create(){

    vector<string> FieldName;	
    vector<string> FieldValue;
    unique_ptr<XaLibChar> LibChar (new XaLibChar());

    string XaMediaId=HTTP.GetHttpParam("XaMedia_ID");
    string File=LibChar->B64Decode(HTTP.GetHttpParam("data"));
    
    int FileSize=File.size();
    double KFileSize = round(FileSize/1024);
    string KSize = FromDoubleToString(KFileSize);
    
    string FileName = ComposeFileName(XaMediaId);
    
    FieldName.push_back("file_name");
    FieldValue.push_back(FileName);
    
    FieldName.push_back("ksize");
    FieldValue.push_back(KSize);

    CreatePrepare({"XaMediaData"},"/XaMediaData/fieldset/field",FieldName,FieldValue);
    CreateExecute("XaMediaData",FieldName,FieldValue);
};

void XaMediaData::Delete(){

    int DeletedId = DeleteExecute("XaMediaData",HTTP.GetHttpParam("id"));
    RESPONSE.Content = DeleteResponse(DeletedId);
};

string XaMediaData::ComposeFileName(string XaMediaId){
	
    string Prefix = XaMediaId + "_";
    
    unique_ptr<XaLibTime> LibTime (new XaLibTime());
    
    string NowTimeMysql=LibTime->GetDateTimeMySql();
    string Suffix=NowTimeMysql.substr(14,2);
    string Name = ClearDate(NowTimeMysql);

    string FileName = Prefix + Name + Suffix;

    return FileName;

};

string XaMediaData::ClearDate(string StringToClear){
    int pos;

    pos=0;
    pos=StringToClear.find("-");

    if (pos !=-1) {

        while (pos!=-1){

            StringToClear.replace(pos,1,"");
            pos=StringToClear.find("-",pos+1);
        }

    }

    pos=0;
    pos=StringToClear.find(":");

    if (pos !=-1) {

        while (pos!=-1){

            StringToClear.replace(pos,1,"");
            pos=StringToClear.find(":",pos+1);
        }

    }

    pos=0;
    pos=StringToClear.find(" ");

    if (pos !=-1) {

        while (pos!=-1){

            StringToClear.replace(pos,1,"");
            pos=StringToClear.find(" ",pos+1);
        }
    }

    return StringToClear;
};

XaMediaData::~XaMediaData(){
};