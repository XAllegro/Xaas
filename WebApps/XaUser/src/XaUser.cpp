#include <XaUser.h>

XaUser::XaUser(){
};

void XaUser::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){
		this->Create();
    } else if (CalledEvent=="Read"){
		this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm"){
		this->ReadForUpdateFrm();
    } else if (CalledEvent=="Update"){
		this->Update();
    } else if (CalledEvent=="Delete"){
		this->Delete();
    } else if (CalledEvent=="List"){
		this->List();
    } else {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}

};

void XaUser::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaUser"},"/XaUser/fieldset/field",FieldName,FieldValue);

	int NextId=CreateExecute("XaUser",FieldName,FieldValue);

	RESPONSE.Content=CreateResponse(NextId);
};

void XaUser::Read() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReturnedFields={"id","name","surname","XaUserType_ID"};

	string Qry="SELECT X.id, X.name, X.surname, XaUserType.name AS XaUserType_ID FROM XaUser X";
	Qry+=" LEFT JOIN XaUserType ON X.XaUserType_ID=XaUserType.id";
	Qry+=" WHERE X.id="+Id;
	Qry+=" AND X.status=1";
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ReadResponse(DbRes,ReturnedFields);
};

void XaUser::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaUser"},"/XaUser/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaUser",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaUser::Update() {

	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

	vector<string> FieldName;	
	vector<string> FieldValue;

	UpdatePrepare({"XaUser"},"/XaUser/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaUser",FieldName,FieldValue,UpdateId);	
	
	RESPONSE.Content=UpdateResponse(Updated);

};

void XaUser::Delete(){

	string Id=HTTP.GetHttpParam("id");
	
	int Deleted=DeleteExecute("XaUser",Id);
	
	RESPONSE.Content=DeleteResponse(Deleted);
};

void XaUser::List (){

	vector<string> ReturnedFields={"id","name","surname","XaUserType_ID"};

	string Qry="SELECT X.id, X.name, X.surname, XaUserType.name AS XaUserType_ID FROM XaUser X";
	Qry+=" LEFT JOIN XaUserType ON X.XaUserType_ID=XaUserType.id";
	Qry+=" WHERE X.status=1";
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);

};

XaUser::~XaUser(){
};