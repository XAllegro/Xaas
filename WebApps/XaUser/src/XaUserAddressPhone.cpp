#include <XaUserAddressPhone.h>
#include <XaLibModel.h>


XaUserAddressPhone::XaUserAddressPhone(){
};

void XaUserAddressPhone::Dispatcher (const string &CalledEvent) {

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

void XaUserAddressPhone::Create() {

    
        vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaUserAddressPhone"},"/XaUserAddressPhone/fieldset/field",FieldName,FieldValue);
        
        string XaTable="XaUser";
        string XaUserId=HTTP.GetHttpParam("XaUser_ID");
        string XaUserAddressPhoneTypeId=HTTP.GetHttpParam("XaUserAddressPhoneType_ID");
        string XaUserAddressPhoneCodeId=HTTP.GetHttpParam("XaUserAddressPhoneCode_ID");
        
        unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        if (LibSql->CheckRow(DB_READ,XaTable,XaUserId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserId+" does not exist into Table -> "+XaTable);
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaUserAddressPhoneType",XaUserAddressPhoneTypeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserAddressPhoneTypeId+" does not exist into Table -> XaUserAddressPhoneType");
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaUserAddressPhoneCode",XaUserAddressPhoneCodeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserAddressPhoneCodeId+" does not exist into Table -> XaUserAddressPhoneCode");
            throw 302;
        }
        
	RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressPhone",FieldName,FieldValue));
};

void XaUserAddressPhone::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressPhone"},"/XaUserAddressPhone/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhone",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressPhone::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressPhone"},"/XaUserAddressPhone/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressPhone",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressPhone"},"/XaUserAddressPhone/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressPhone",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressPhone::Update() {

	int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaUserAddressPhone"},"/XaUserAddressPhone/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaUserAddressPhone",FieldName,FieldValue,Id));
};

void XaUserAddressPhone::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressPhone",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressPhone::~XaUserAddressPhone(){
};