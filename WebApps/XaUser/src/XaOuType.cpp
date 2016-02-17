#include <XaOuType.h>
#include <XaLibModel.h>


XaOuType::XaOuType(){
};

void XaOuType::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
		 this->Read();
    } else if (CalledEvent=="List"){
		 this->List();
    } else if (CalledEvent=="ListAsOptions"){
		 this->ListAsOptions();
    } else if (CalledEvent=="Update"){
		 this->Update();
    } else if (CalledEvent=="Delete"){
		 this->Delete();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOuType::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaOuType"},"/XaOuType/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=CreateResponse(CreateExecute("XaOuType",FieldName,FieldValue));
};

void XaOuType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaOuType"},"/XaOuType/fieldset/field",1);
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOuType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaOuType::List() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
	string PassedOrderBy=HTTP.GetHttpParam("order_by");
	
	if (PassedOrderBy!="NoHttpParam") {
	
		OrderByFields.push_back(PassedOrderBy);
	};
	
	/*STATUS*/
	string PassedStatus=HTTP.GetHttpParam("status");
	
	if (PassedStatus!="NoHttpParam") {

		WhereFields.push_back("status");
		WhereValues.push_back(PassedStatus);
	};

	vector<string> ReturnedFields=ListPrepare({"XaOuType"},"/XaOuType/fieldset/field",1);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOuType",{ReturnedFields},{WhereFields},{WhereValues},{OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaOuType::ListAsOptions() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
	string PassedOrderBy=HTTP.GetHttpParam("order_by");
	
	if (PassedOrderBy!="NoHttpParam") {
	
		OrderByFields.push_back(PassedOrderBy);
	};
	
	/*STATUS*/
	string PassedStatus=HTTP.GetHttpParam("status");
	
	if (PassedStatus!="NoHttpParam") {

		WhereFields.push_back("status");
		WhereValues.push_back(PassedStatus);
	};

	vector<string> ReturnedFields={"id","name"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOuType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaOuType::Update() {

	BackupRecord("XaOuType",50);

	/*
	XaLibBase::FieldsMap LoadedFields=UpdatePrepare({"XaOuType"},"/XaOuType/fieldset/field");
	RESPONSE.Content=CreateResponse(UpdateExecute("XaOuType",LoadedFields));*/
};

void XaOuType::Delete() {

	int DeletedId=DeleteExecute("XaOuType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

/*

XaOuModel::Update(){
};



XaOuModel::XaOuModel(){
};
*/
XaOuType::~XaOuType(){
};