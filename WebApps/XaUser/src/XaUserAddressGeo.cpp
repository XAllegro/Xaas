#include <XaUserAddressGeo.h>
#include <XaLibModel.h>


XaUserAddressGeo::XaUserAddressGeo(){
};

void XaUserAddressGeo::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
		 this->Read();
    } else if (CalledEvent=="List"){
		 this->List();
    } else if (CalledEvent=="Update"){
		 this->Update();
    } else if (CalledEvent=="Delete"){
		 this->Delete();
    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserAddressGeo::Create() {

        vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaUserAddressGeo"},"/XaUserAddressGeo/fieldset/field",FieldName,FieldValue);
        
        string XaTable="XaUser";
        string XaUserId=HTTP.GetHttpParam("XaUser_ID");
        string XaUserAddressGeoTypeId=HTTP.GetHttpParam("XaUserAddressGeoType_ID");
        
        unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        if (LibSql->CheckRow(DB_READ,XaTable,XaUserId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserId+" does not exist into Table -> "+XaTable);
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaUserAddressGeoType",XaUserAddressGeoTypeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserAddressGeoTypeId+" does not exist into Table -> XaUserAddressGeoType");
            throw 302;
        }
        
	RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressGeo",FieldName,FieldValue));
};

void XaUserAddressGeo::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressGeo"},"/XaUserAddressGeo/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressGeo",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressGeo::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressGeo"},"/XaUserAddressGeo/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressGeo",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressGeo"},"/XaUserAddressGeo/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressGeo",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressGeo::Update() {

	int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaUserAddressGeo"},"/XaUserAddressGeo/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaUserAddressGeo",FieldName,FieldValue,Id));
};

void XaUserAddressGeo::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressGeo",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressGeo::~XaUserAddressGeo(){
};