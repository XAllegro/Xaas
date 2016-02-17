#include <XaUserAddressPhoneType.h>
#include <XaLibModel.h>


XaUserAddressPhoneType::XaUserAddressPhoneType(){
};

void XaUserAddressPhoneType::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressPhoneType::Create() {

        vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressPhoneType",FieldName,FieldValue));
};

void XaUserAddressPhoneType::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhoneType",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressPhoneType::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReturnedFields={"id","name","description"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhoneType",{ReturnedFields},{"id"},{Id});

	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaUserAddressPhoneType::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhoneType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressPhoneType",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressPhoneType::ListAsOptions() {

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

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhoneType",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaUserAddressPhoneType::Update() {

	int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaUserAddressPhoneType"},"/XaUserAddressPhoneType/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaUserAddressPhoneType",FieldName,FieldValue,Id));
};

void XaUserAddressPhoneType::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressPhoneType",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressPhoneType::~XaUserAddressPhoneType(){
};