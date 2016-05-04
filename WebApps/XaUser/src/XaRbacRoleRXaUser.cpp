#include <XaRbacRoleRXaUser.h>
#include <XaLibModel.h>


XaRbacRoleRXaUser::XaRbacRoleRXaUser(){
};

void XaRbacRoleRXaUser::Dispatcher (const string &CalledEvent) {
	
	if (CalledEvent=="GetXmlModel"){
		this->GetXmlModel();
	} else if (CalledEvent=="Create"){
		this->Create();
    } else if (CalledEvent=="ListByUser"){
		this->ListByUser();
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

void XaRbacRoleRXaUser::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaRbacRoleRXaUser"},"/XaRbacRoleRXaUser/fieldset/field",FieldName,FieldValue);

	int NextId=CreateExecute("XaRbacRole_R_XaUser",FieldName,FieldValue);

	RESPONSE.Content=CreateResponse(NextId);
};

void XaRbacRoleRXaUser::ListByUser() {

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	string Qry="SELECT XaRbacRole_R_XaUser.id,XaRbacRole.name,XaRbacRole.description,XaRbacRole_R_XaUser.XaRbacRole_ID "
				"FROM XaRbacRole,XaRbacRole_R_XaUser "
				"WHERE XaRbacRole_R_XaUser.XaRbacRole_ID=XaRbacRole.id AND XaRbacRole_R_XaUser.status=1 "
				"AND XaRbacRole_R_XaUser.XaUser_ID="+XaUser_ID +" ORDER BY XaRbacRole.name";

	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,Qry);

	vector<string>  ReturnedFields={"id","XaRbacRole_ID","description","name"};

	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};
/*
void XaRbacRoleRXaUser::ListByUser (){

	string XaUser_ID=HTTP.GetHttpParam("XaUser_ID");

	vector<string> ReturnedFields={"id","XaRbacRole_ID"};

	string Qry="SELECT X.id, XaRbacRole.name AS XaRbacRole_ID FROM XaRbacRole_R_XaUser X";
	Qry+=" LEFT JOIN XaRbacRole ON X.XaRbacRole_ID=XaRbacRole.id";
	Qry+=" WHERE X.XaUser_ID="+XaUser_ID;
	Qry+=" AND X.status=1";
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);

};
*/
void XaRbacRoleRXaUser::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaRbacRoleRXaUser"},"/XaRbacRoleRXaUser/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaRbacRole_R_XaUser",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaRbacRoleRXaUser::Update() {

	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

	vector<string> FieldName;	
	vector<string> FieldValue;

	UpdatePrepare({"XaRbacRoleRXaUser"},"/XaRbacRoleRXaUser/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaRbacRole_R_XaUser",FieldName,FieldValue,UpdateId);	

	RESPONSE.Content=UpdateResponse(Updated);

};

void XaRbacRoleRXaUser::Delete() {

	string Id=HTTP.GetHttpParam("id");
	int Deleted=DeleteExecute("XaRbacRole_R_XaUser",Id);
	RESPONSE.Content=DeleteResponse(Deleted);
};

XaRbacRoleRXaUser::~XaRbacRoleRXaUser(){
};
