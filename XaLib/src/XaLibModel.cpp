#include <XaLibModel.h>

XaLibModel::XaLibModel() {
};

/*TO REMOVE*/
void XaLibModel::DumpDbResMap(DbResMap& ResMap) {
/*
	for (auto i=0;i<ResMap.size();i++) {
	
		for (const auto &k:ResMap[i]) {

			//LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"YYYYYYYYYY -> "+k.first+" :: " +k.second);
		};
	
	};
*/
};

vector<string> XaLibModel::AddXmlFile(const vector<string>& FileName){

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

void XaLibModel::CreatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue){

	vector <string> Properties ={"name","db_type","size","create","required"};
	
	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
		
		string FDbType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/db_type");
		string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
		string FCreate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/create");
		string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

		string FValue=HTTP.GetHttpParam(FName);

		FieldName.push_back(FName);
		FieldValue.push_back(FValue);
	};
};

int XaLibModel::CreateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue) {

	FieldName.push_back("status");
	FieldName.push_back("updated_by");
	FieldValue.push_back("1");
	FieldValue.push_back(FromIntToString(SESSION.XaUser_ID));
	
	
	//CHECK FIELDS
	//vector <string> Fields={"status","old_id"};
	//vector <string> Values={"1","0"};
/*
	for (auto i=0;i<LoadedFields.size();i++) {

		Fields.push_back(LoadedFields[i]["name"]);	
		Values.push_back(LoadedFields[i]["value"]);
	};
*/
	int NextId=XaLibSql::Insert(DB_WRITE,DbTable,FieldName,FieldValue);

	if (NextId==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-301 Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));
		throw 301;
	}

	int UpdatedOrig=XaLibSql::Update(DB_WRITE,DbTable,{"orig_id"},{FromIntToString(NextId)},{"id"},{FromIntToString(NextId)});

	if (UpdatedOrig==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-3011 Failed to initialize orig_id for a new record into table -> "+DbTable+" with id ->"+to_string(NextId));
		throw 3011;
	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));

	return NextId;
};

string XaLibModel::CreateResponse(const int& NextId) {

	return "<create>"+to_string(NextId)+"</create>";
};

vector<string> XaLibModel::ReadPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields) {

	//TODO:GESTIONE ERRORI
	vector<string> FieldsToRead;

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);
	
	for (auto i=0;i<FieldsNum;i++) {
		
		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/read")=="yes"){
		
			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};
		
	};
	
	auto it = FieldsToRead.begin();
	it = FieldsToRead.insert ( it , "id" );

	if (WithSystemFields==1) {
		FieldsToRead.push_back("updated_by");
		FieldsToRead.push_back("updated");
		FieldsToRead.push_back("status");
		FieldsToRead.push_back("orig_id");
	}

	//SE E" VUOTO
	return FieldsToRead;
};

string XaLibModel::ReadResponse(DbResMap& DbRes,vector<string>& FieldsToRead) {

	string Res="<read>";
	
	for (auto &i: FieldsToRead) {
			
		Res.append("<"+i+">");
		Res.append(DbRes[0][i]);
		Res.append("</"+i+">");
	};

	Res.append("</read>");
	return Res;	
};

vector<string> XaLibModel::ListPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields) {

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	vector<string> FieldsToRead;

	for (auto i=0;i<FieldsNum;i++) {

		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/list")=="yes") {

			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field to retrieve for the list ->"+FieldsToRead[i]);
	};

	
	auto it = FieldsToRead.begin();
	it = FieldsToRead.insert ( it , "id" );

	if (WithSystemFields==1) {
		FieldsToRead.push_back("updated_by");
		FieldsToRead.push_back("updated");
		FieldsToRead.push_back("status");
		FieldsToRead.push_back("orig_id");
	}

	return FieldsToRead;
};

string XaLibModel::ListResponse(DbResMap& DbRes,vector<string>& FieldsToRead) {

	string Res="<list>";

	for (auto j=0;j<DbRes.size();j++) {
	
		Res.append("<item>");

		for (auto &i: FieldsToRead) {

			Res.append("<"+i+">");
			
			if (DbRes[j][i]=="") {
				Res.append("null");

			} else {
			
				Res.append(DbRes[j][i]);
			}

			//Res.append(DbRes[j][i]);
			Res.append("</"+i+">");
			
		};

		Res.append("</item>");
	};

	Res.append("</list>");
	return Res;	
};

int XaLibModel::BackupRecord(const string& DbTable,const int& FieldId) {

	vector<string> Columns=XaLibSql::ColumnsList(DB_READ,DbTable);
	
	/* all other columns, included "updated", must be preserved */
	vector<string> ExcludeToList={"id","status"};

	string List={};

	for(int i=0;i<Columns.size();i++) {

		auto it = find (ExcludeToList.begin(), ExcludeToList.end(), Columns[i]);

		if (it != ExcludeToList.end()) {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Found In The Exclusion List -> "+Columns[i]);

		} else {

			List.append(Columns[i]+",");
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field List Appending -> "+Columns[i]);
		}
	};

	//REMOVE LAST ","
	//string SqlCopiedColumns=List.substr(0, List.size()-1);
	//keep last comma since it is used to append SqlUpdatedColumns,SqlUpdatedValues later on
	string SqlCopiedColumns=List;

	string SqlUpdatedColumns="status";
	string SqlUpdatedValues="'3'";

	string SqlQry="INSERT INTO " + DbTable+" (" +SqlCopiedColumns + SqlUpdatedColumns +") SELECT "+SqlCopiedColumns + SqlUpdatedValues +" FROM "+DbTable+" WHERE id="+FromIntToString(FieldId); 

	unsigned NextId=XaLibSql::FreeQueryInsert(DB_WRITE,SqlQry);

	/* NO UPDATES allowed on the record just inserted, since they would alter the "updated" column, which must keep its previous value */

};

void XaLibModel::UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue){

	vector <string> Properties ={"name","db_type","size","create","required"};
	
	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
		string FUpdate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update");

		if (FUpdate=="yes") {
			string FDbType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/db_type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

			string FValue=HTTP.GetHttpParam(FName);

			FieldName.push_back(FName);
			FieldValue.push_back(FValue);
		}
	};
};

int XaLibModel::UpdateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue, const int& Id) {

	FieldName.push_back("updated_by");
	FieldValue.push_back(FromIntToString(SESSION.XaUser_ID));

	BackupRecord(DbTable,Id);

	int Updated=XaLibSql::Update(DB_WRITE,DbTable,{FieldName},{FieldValue},{"id"},{XaLibBase::FromIntToString(Id)});

	if (Updated==1) {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated a record into table -> "+DbTable+" with id ->"+to_string(Id));
		return Id;
	} else {
		return 0;
	}

};

string XaLibModel::UpdateResponse(const int& UpdatedId) {

	return "<update>"+to_string(UpdatedId)+"</update>";
};

int XaLibModel::DeleteExecute(const string& DbTable,const string& FieldId) {

	//TODO: ERROR CHECK
	if (XaLibSql::Update(DB_WRITE,DbTable,{"status"},{"4"},{"id"},{FieldId})==1){
	
		return FromStringToInt(FieldId);

	} else {

		return 0;
	}

};

string XaLibModel::DeleteResponse(const int& DeletedId) {

	return "<delete>"+to_string(DeletedId)+"</delete>";
};

/*
void XaLibModel::ResetPoperites () {

	Fields.empty();
	Values.empty();
	ReturnedFields.empty();
	WhereFields.empty();
	WhereValues.empty();
	OrderByFields.empty();
	GroupByFields.empty();
	Limit=0;
};
*/
/*
 se voglio properties->property nell'xml passo Properties,property
 */
/*
string XaLibModel::BuildXml(DbResMap& ResMap,const string& Container,const string& GroupBy) {
	
	string Xml="";
	Xml.append("<").append(Container).append(">");
	
	for (auto i=0;i<ResMap.size();i++) {

		Xml.append("<").append(GroupBy).append(">");

		for (auto j=0;j<ReturnedFields.size();j++) {
			
			Xml.append("<").append(ReturnedFields[j]).append(">");
			Xml.append(ResMap[i][ReturnedFields[j]]);
			Xml.append("</").append(ReturnedFields[j]).append(">");
		}

		Xml.append("</").append(GroupBy).append(">");
	}

	Xml.append("</").append(Container).append(">");

	return Xml;
};
*/
void XaLibModel::Execute(){

	//EXECUTE OBJECT DISPATCHER (CLASS DISPATCHER)
	if (REQUEST.CalledObject!="" && REQUEST.CalledEvent!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Object Event ->"+REQUEST.CalledEvent);
		this->Dispatcher(REQUEST.CalledEvent);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Event Is empty");
		throw 41;
	}

};

XaLibModel::~XaLibModel(){
};