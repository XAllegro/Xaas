#include <XaUser.h>

XaUser::XaUser(){
};

void XaUser::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Login"){
        this->Login();
    } else if (CalledEvent=="Logout"){
		this->Logout();
    } else if (CalledEvent=="Create"){
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

/*TEST CASE
 TUTTE LE COMBINAZIONI
 */
void XaUser::Login (){

	string StrUsername=HTTP.GetHttpParam("username");
	string StrPassword=HTTP.GetHttpParam("password");

	if (StrUsername !="" && StrPassword !="") {

		string ShaPassword=XaLibCrypto::GetSha1(StrPassword);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Encrypted Password -> "+ShaPassword);
		
		string SqlQry="SELECT id FROM XaUser WHERE username=\""+StrUsername+"\" AND password=\""+ShaPassword+"\" AND status in (0,1)";
		DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

		int n=DbRes.size();

		if (n==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-45 USER Does Not Exist Or The Password Is Wrong -> " + StrUsername);
			throw 45;

		} else if (n==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Valid With ID ->"+DbRes[0]["id"]);

			XaLibToken LibToken;

			int TokenCheck=LibToken.CheckUserToken(atoi(DbRes[0]["id"].c_str()));

			if (TokenCheck==1) {

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER already has a Token to Deactivate");
				LibToken.DeactivateUserToken (atoi(DbRes[0]["id"].c_str()));
			}

			SESSION.Token=LibToken.CreateToken(FromStringToInt(DbRes[0]["id"]));

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Valid With ID ->"+DbRes[0]["id"]+" And Token  ->"+RESPONSE.Content);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-46 User Is Not Unique");
			throw 46;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-47 Username Or Password Is Empty");
		throw 47;
	}

};

void XaUser::Logout () {

	XaLibToken::DeactivateUserToken(SESSION.Token);
	
	SESSION.Token="0";
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Logout Affected");
};

void XaUser::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaUser"},"/XaUser/fieldset/field",FieldName,FieldValue);

	FieldName.push_back("leaf");
	FieldValue.push_back("1");

	/*Get parent level*/
	int pos=PositionInVector(FieldName,"tree_parent_ID");

	if (pos==-1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-206:: Searched Element is Not present in the Vector");
		throw 206;
	};

	string tree_parent_ID= FieldValue[pos];

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Retrieved tree_parent_ID ->"+ tree_parent_ID);

	DbResMap Parent=XaLibSql::Select(DB_READ,"XaOu",{"id","tree_level","tree_path"},{"id"},{tree_parent_ID});

	if (Parent.size()!=1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-304:: The record is not unique");
		throw 304;
	};

	/*CALCULATING TREE LEVEL*/
	string TreeLevel=FromIntToString((FromStringToInt(Parent[0]["tree_level"])+1));

	FieldName.push_back("tree_level");
	FieldValue.push_back(TreeLevel);

	int NextId=CreateExecute("XaUser",FieldName,FieldValue);

	/*CALCULATING TREE PATH*/
	string TreePath=Parent[0]["tree_path"]+FromIntToString(NextId)+"|";

	XaLibSql::Update(DB_WRITE,"XaUser",{"tree_path"},{TreePath},{"id"},{FromIntToString(NextId)});

	RESPONSE.Content=CreateResponse(NextId);
};

void XaUser::Read() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaUser"},"/XaUser/fieldset/field",0);

	string Qry="SELECT name,surname,tree_parent_ID FROM XaUser WHERE id="+Id;
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
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

	string TreeParentId=HTTP.GetHttpParam("tree_parent_ID");

	vector<string> ReturnedFields={"id","name","surname","XaUserType_ID","XaUserRole_ID","tree_parent_ID"};

	string Qry="SELECT X.id, X.name, X.surname, XaUserType.name AS XaUserType_ID, XaUserRole.name AS XaUserRole_ID, XaOu.name AS tree_parent_ID FROM XaUser X";
	Qry+=" LEFT JOIN XaUserType ON X.XaUserType_ID=XaUserType.id";
	Qry+=" LEFT JOIN XaUserRole ON X.XaUserRole_ID=XaUserRole.id";
	Qry+=" LEFT JOIN XaOu ON X.tree_parent_ID=XaOu.id";
	Qry+=" WHERE X.tree_parent_ID="+TreeParentId;
	Qry+=" AND X.status=1";
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);

};

XaUser::~XaUser(){
};