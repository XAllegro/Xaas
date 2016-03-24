#include <XaUserType.h>
#include <XaLibModel.h>


XaUserType::XaUserType(){
};

void XaUserType::Dispatcher (const string &CalledEvent) {
	
	if (CalledEvent=="GetXmlModel"){
		this->GetXmlModel();
	} else if (CalledEvent=="Create"){
		this->Create();
    } else if (CalledEvent=="List"){
		 this->List();
    } else if (CalledEvent=="ListAsOptions"){
		 this->ListAsOptions();
    } else if (CalledEvent=="Read"){
		 this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm"){
		 this->ReadForUpdateFrm();
    } else if (CalledEvent=="Update"){
		 this->Update();
    } else if (CalledEvent=="Delete"){
		 this->Delete();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42:: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserType::GetXmlModel() {

	ifstream MyFile;
	string Content;

	vector<string> XmlFiles=AddXmlFile({"XaUserType"});

	for (auto i=0;i<XmlFiles.size();i++) {

		MyFile.open(XmlFiles[i].c_str());

		if (MyFile.is_open()) {

			string TmpString;

			while(getline(MyFile,TmpString)) {
				XaLibChar::ClearReturn(TmpString);
				Content.append(TmpString);
			}
		}
	}

	RESPONSE.Content="<createfrm>"+Content+"</createfrm>";	

};

void XaUserType::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaUserType"},"/XaUserType/fieldset/field",FieldName,FieldValue);

	int NextId=CreateExecute("XaUserType",FieldName,FieldValue);

	RESPONSE.Content=CreateResponse(NextId);
};

void XaUserType::List (){

	vector<string> ListFields=ListPrepare({"XaUserType"},"/XaUserType/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserType",{ListFields},{"status"},{"1"});

	RESPONSE.Content=ListResponse(DbRes,ListFields);

};

void XaUserType::ListAsOptions() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/* only option with id=passed value */
	string CurrentValue=HTTP.GetHttpParam("value");
	if (CurrentValue!="NoHttpParam") {
		WhereFields.push_back("id");
		WhereValues.push_back(CurrentValue);
	}
	
	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
	OrderByFields.push_back("name");
	string PassedOrderBy=HTTP.GetHttpParam("order_by");
	
	if (PassedOrderBy!="NoHttpParam") {
		OrderByFields.push_back(PassedOrderBy);
	};
	
	/*STATUS*/
	string PassedStatus="1";//HTTP.GetHttpParam("status");
	
	if (PassedStatus!="NoHttpParam") {

		WhereFields.push_back("status");
		WhereValues.push_back(PassedStatus);
	};

	//vector<string> ReturnedFields=ListPrepare({"XaOuType"},"/XaOuType/fieldset/field");

	vector<string> ReturnedFields={"id","name"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaUserType::Read() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaUserType"},"/XaUserType/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserType",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaUserType::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaUserType"},"/XaUserType/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserType",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaUserType::Update() {

	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

	vector<string> FieldName;	
	vector<string> FieldValue;

	UpdatePrepare({"XaUserType"},"/XaUserType/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaUserType",FieldName,FieldValue,UpdateId);	
	
	/* Parent Id and tree are not updatable yet */
	/* Tree updates will have to be propagated to all descendants */
	
	RESPONSE.Content=UpdateResponse(Updated);

};

void XaUserType::Delete(){

	string Id=HTTP.GetHttpParam("id");
	
	int Deleted=DeleteExecute("XaUserType",Id);
	
	RESPONSE.Content=DeleteResponse(Deleted);
};

XaUserType::~XaUserType(){
};
