#include <XaUserAddressMail.h>
#include <XaLibModel.h>


XaUserAddressMail::XaUserAddressMail(){
};

void XaUserAddressMail::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="GetXmlModel"){
		this->GetXmlModel();
	} else if (CalledEvent=="Create"){
		this->Create();
    } else if (CalledEvent=="Read"){
		this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm") {
		this->ReadForUpdateFrm();
    } else if (CalledEvent=="List"){
		 this->List();
    } else if (CalledEvent=="ListByUser"){
		 this->ListByUser();
    } else if (CalledEvent=="Update"){
		 this->Update();
    } else if (CalledEvent=="Delete"){
		 this->Delete();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaUserAddressMail::Create() {
        
	vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field",FieldName,FieldValue);
	
        string XaTable="XaUser";
        string XaUserId=HTTP.GetHttpParam("XaUser_ID");
        string XaUserAddressMailTypeId=HTTP.GetHttpParam("XaUserAddressMailType_ID");
        
        unique_ptr<XaLibSql> LibSql (new XaLibSql());
        
        if (LibSql->CheckRow(DB_READ,XaTable,XaUserId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserId+" does not exist into Table -> "+XaTable);
            throw 302;
        }
        
        if (LibSql->CheckRow(DB_READ,"XaUserAddressMailType",XaUserAddressMailTypeId,"1","")==0) {
            LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Record ID -> "+XaUserAddressMailTypeId+" does not exist into Table -> XaUserAddressMailType");
            throw 302;
        }
        
        RESPONSE.Content=CreateResponse(CreateExecute("XaUserAddressMail",FieldName,FieldValue));
};

void XaUserAddressMail::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaUserAddressMail::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaUserAddressMail::List() {

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

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");
	DbResMap DbRes = ReadExecute("XaUserAddressMail",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaUserAddressMail::ListByUser() {

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	vector<string> WhereFields={"XaUser_ID","status"};
	vector<string> WhereValues={XaUser_ID,"1"};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	int Limit={0};

	string OrderBy=HTTP.GetHttpParam("order_by");

	vector<string> ReturnedFields=ListPrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUserAddressMail",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	

};

void XaUserAddressMail::Update() {

	int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaUserAddressMail"},"/XaUserAddressMail/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaUserAddressMail",FieldName,FieldValue,Id));
};

void XaUserAddressMail::Delete() {

	int DeletedId=DeleteExecute("XaUserAddressMail",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

XaUserAddressMail::~XaUserAddressMail(){
};