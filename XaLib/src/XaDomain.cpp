#include <XaDomain.h>
#include <XaLibModel.h>


XaDomain::XaDomain(){
};

void XaDomain::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
        this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm"){
        this->ReadForUpdateFrm();
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

void XaDomain::Create() {

        vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaDomain"},"/XaDomain/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=CreateResponse(CreateExecute("XaDomain",FieldName,FieldValue));
};

void XaDomain::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaDomain::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaDomain::List() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	string OrderBy=HTTP.GetHttpParam("order_by");
	string Status=HTTP.GetHttpParam("status");

	vector<string> ReturnedFields=ListPrepare({"XaDomain"},"/XaDomain/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field");
	DbResMap DbRes = ReadExecute("XaDomain",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaDomain::ListAsOptions() {
        string Domain=HTTP.GetHttpParam("domain");
	string TreeParentId=HTTP.GetHttpParam("tree_parent_ID");
        
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
        
        if (Domain!="NoHttpParam") {

		WhereFields.push_back("domain");
		WhereValues.push_back(Domain);
	};
        
        if (TreeParentId!="NoHttpParam") {

		WhereFields.push_back("tree_parent_ID");
		WhereValues.push_back(TreeParentId);
	};

	vector<string> ReturnedFields={"id","name"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaDomain::Update() {
        
        int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaDomain"},"/XaDomain/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaDomain",FieldName,FieldValue,Id));
};

void XaDomain::Delete() {

	int DeletedId=DeleteExecute("XaDomain",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaDomain::~XaDomain(){
};