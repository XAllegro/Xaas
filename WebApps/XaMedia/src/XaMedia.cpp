#include <XaMedia.h>
#include <XaLibModel.h>
#include <XaLibTime.h>

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
    }else if (CalledEvent=="CreateComplete"){
        this->CreateComplete();
    }else if (CalledEvent=="Delete"){
	this->Delete();
    }else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }

};

void XaMedia::List(){
    
	string XaDomainMediaCategory_ID=HTTP.GetHttpParam("XaDomainMediaCategory_ID");
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
	Qry+=" WHERE R.status=1 AND R.XaField_ID="+XaField_ID+" AND R.XaTable='"+XaTable+"' AND R.XaDomainMediaCategory_ID="+XaDomainMediaCategory_ID;

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

void XaMedia::CreateComplete(){

    string Type=HTTP.GetHttpParam("type");
    string Name=HTTP.GetHttpParam("name");
    string XaDomainMediaCategoryId="";
    
    if (Type.substr(0,5)=="image") {
        XaDomainMediaCategoryId="854";
    } else {
        XaDomainMediaCategoryId="857";
    }
    
    vector<string> FieldName;	
    vector<string> FieldValue;

    vector<string> FieldNameMedia;
    vector<string> FieldValueMedia;
    vector<string> FieldNameData;
    vector<string> FieldValueData;
    
    // standard method CreatePrepare is run only to check field format and requirement
    CreatePrepare({"XaMediaComplete"},"/XaMediaComplete/fieldset/field",FieldName,FieldValue);
    //CreateExecute("XaMedia",FieldName,FieldValue);
    
    FieldNameMedia.push_back("XaTable");
    FieldValueMedia.push_back(HTTP.GetHttpParam("XaTable"));
    FieldNameMedia.push_back("XaField_ID");
    FieldValueMedia.push_back(HTTP.GetHttpParam("XaField_ID"));
    FieldNameMedia.push_back("XaDomainMediaCategory_ID");
    //FieldValueMedia.push_back(HTTP.GetHttpParam("XaDomainMediaCategory_ID"));
    FieldValueMedia.push_back(XaDomainMediaCategoryId);
    FieldNameMedia.push_back("preferred");
    FieldValueMedia.push_back("2");
    
    int MediaId=CreateExecute("XaMedia",FieldNameMedia,FieldValueMedia);
    
    //unique_ptr<XaLibChar> LibChar (new XaLibChar());
    
    string XaMediaId=FromIntToString(MediaId);
    //string File=LibChar->B64Decode(HTTP.GetHttpParam("data","B64"));
    
    string File=HTTP.GetHttpParam("data","B64");
    
    int FileSize=File.size();
    double KFileSize = round(FileSize/1024);
    string KSize = FromDoubleToString(KFileSize);
    
    string FileName = ComposeFileName(XaMediaId);
    
    FieldNameData.push_back("XaMedia_ID");
    FieldValueData.push_back(XaMediaId);
    
    FieldNameData.push_back("file_name");
    FieldValueData.push_back(FileName);
    
    FieldNameData.push_back("data");
    FieldValueData.push_back(File);
    
    FieldNameData.push_back("ksize");
    FieldValueData.push_back(KSize);
    
    FieldNameData.push_back("type");
    FieldValueData.push_back(Type);
    
    FieldNameData.push_back("name");
    FieldValueData.push_back(Name);

    int DataId=CreateExecute("XaMediaData",FieldNameData,FieldValueData);
    
    RESPONSE.Content="<create_media><id>"+FromIntToString(MediaId)+"</id></create_media><create_data><id>"+FromIntToString(DataId)+"</id></create_data>";
}

void XaMedia::Delete(){

    int DeletedId = DeleteExecute("XaMedia",HTTP.GetHttpParam("id"));
    RESPONSE.Content = DeleteResponse(DeletedId);
};

string XaMedia::ComposeFileName(string XaMediaId){
	
    string Prefix = XaMediaId + "_";
    
    unique_ptr<XaLibTime> LibTime (new XaLibTime());
    
    string NowTimeMysql=LibTime->GetDateTimeMySql();
    string Suffix=NowTimeMysql.substr(14,2);
    string Name = ClearDate(NowTimeMysql);

    string FileName = Prefix + Name + Suffix;

    return FileName;

};

string XaMedia::ClearDate(string StringToClear){
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

XaMedia::~XaMedia(){
};