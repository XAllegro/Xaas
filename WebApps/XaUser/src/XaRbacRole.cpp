#include <XaRbacRole.h>
#include <XaLibModel.h>


XaRbacRole::XaRbacRole(){
};

void XaRbacRole::Dispatcher (const string &CalledEvent) {
	
	if (CalledEvent=="Create"){
		this->Create();
    } else if (CalledEvent=="List"){
		 this->List();
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

void XaRbacRole::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaRbacRole"},"/XaRbacRole/fieldset/field",FieldName,FieldValue);

	int NextId=CreateExecute("XaRbacRole",FieldName,FieldValue);

	RESPONSE.Content=CreateResponse(NextId);
};

void XaRbacRole::List (){

	vector<string> ListFields=ListPrepare({"XaRbacRole"},"/XaRbacRole/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaRbacRole",{ListFields},{"status"},{"1"});

	RESPONSE.Content=ListResponse(DbRes,ListFields);

};

void XaRbacRole::Read() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaRbacRole"},"/XaRbacRole/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaRbacRole",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaRbacRole::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaRbacRole"},"/XaRbacRole/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaRbacRole",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaRbacRole::Update() {

	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

	vector<string> FieldName;	
	vector<string> FieldValue;

	UpdatePrepare({"XaRbacRole"},"/XaRbacRole/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaRbacRole",FieldName,FieldValue,UpdateId);	
	
	/* Parent Id and tree are not updatable yet */
	/* Tree updates will have to be propagated to all descendants */
	
	RESPONSE.Content=UpdateResponse(Updated);

};

void XaRbacRole::Delete(){

	string Id=HTTP.GetHttpParam("id");
	
	int Deleted=DeleteExecute("XaRbacRole",Id);
	
	RESPONSE.Content=DeleteResponse(Deleted);
};

XaRbacRole::~XaRbacRole(){
};
