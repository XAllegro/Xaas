#include <XaLibToken.h>
#include <XaLibCrypto.h>

XaLibToken::XaLibToken(){
};

int XaLibToken::ValidateToken(const string& Token) {

	string SqlQry="SELECT XaUser_ID FROM XaUserToken WHERE status=1 AND token=\""+Token+"\"";
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

	if (DbRes.size()!=0){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is valid for XaUser_ID-> "+ DbRes[0]["XaUser_ID"]);
		return atoi(DbRes[0]["XaUser_ID"].c_str());

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is Not Valid");
		throw 52;
	}
};

int XaLibToken::RetrieveUserFromToken(const string& Token) {

	string SqlQry="SELECT XaUser_ID FROM XaUserToken WHERE status=1 AND token=\""+Token+"\"";
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

	if (DbRes.size()==0){
		/*Requested Logout for auser not logged in*/
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN did not find any User_ID associated to this token->"+ Token);
		return 0;

	} else if (DbRes.size()==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN 1 User is associated to this token XaUser_ID-> "+ DbRes[0]["XaUser_ID"]);
		return atoi(DbRes[0]["XaUser_ID"].c_str());

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN More tokens are associated to this User or more users have this token");
		throw 54;
	}
};

int XaLibToken::CheckUserToken(const int& XaUser_ID) {

	string SqlQry="SELECT id FROM XaUserToken WHERE status=1 AND XaUser_ID=\""+to_string(XaUser_ID)+"\"";
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

	if (DbRes.size()!=0){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is valid for XaUser_ID-> "+ DbRes[0]["XaUser_ID"]);
		//return atoi(DbRes[0]["XaUser_ID"].c_str());
		return 1;

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Is Not Valid");
		return 0;
	}
};

void XaLibToken::DeactivateUserToken(const int& XaUser_ID) {

	int Updated=XaLibSql::Update(DB_SESSION,"XaUserToken",{"status"},{"2"}, {"XaUser_ID"},{to_string(XaUser_ID)});
	
	if (Updated==1 ) {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deactivated Token For User Id-> "+ to_string(XaUser_ID));

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-55 Deactivating Token For User Id -> "+ to_string(XaUser_ID));
		throw 55;
	}
};

void XaLibToken::DeactivateUserToken(const string& Token) {

	
	int Updated=XaLibSql::Update(DB_SESSION,"XaUserToken",{"status"},{"2"}, {"token"},{Token});

	if (Updated ==1 ) {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Deactivated Token -> "+ Token);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-53 Deactivating Token -> "+ Token);
		throw 53;
	}
};

/* TESTARE IL CASO DI TOKEN DUPLICATO */
string XaLibToken::CreateToken(const int& XaUser_ID) {

	string Token=GenerateToken();

	XaLibSql LibSql;
	LibSql.LockTable(DB_SESSION,"XaUserToken");
	
	string SqlQry="SELECT id FROM XaUserToken WHERE token=\""+Token+"\"";
	DbResMap DbRes=LibSql.FreeQuerySelect(DB_SESSION,SqlQry);

	//VERIFING DOES NOT EXIST IN THE DATABASE
	if (DbRes.size()!=0){

		LibSql.UnlockTable(DB_SESSION);
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Generated Token Already Exists");
		
		this->CreateToken(XaUser_ID);

		//mettere un limite al numero tentativi xon un contatore privato

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Generated Token Is Valid");

		vector<string> VectorFields {"XaUser_ID","token","status"};
		vector<string> VectorValues{FromIntToString(XaUser_ID),Token,"1"};

		int NextId=LibSql.Insert(DB_SESSION,"XaUserToken",VectorFields,VectorValues);
		LibSql.UnlockTable(DB_SESSION);

		if (NextId==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TOKEN Error Inserting a new TOKEN into database");
			throw 51;

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN -> Inserted a new Token into Database" + XaLibBase::FromIntToString(NextId));
		}	
	}

	return Token;
};

string XaLibToken::GenerateToken(){

	mt19937_64 generator (chrono::system_clock::now().time_since_epoch().count());
	string MtSring=to_string(generator());

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Generated Mersenne Key ->"+ MtSring);

	string SeedString=MtSring+SESSION.ClientIp;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"TOKEN Generated Browser Signature ->"+ SeedString);

	return XaLibCrypto::GetSha1(SeedString);;
};

XaLibToken::~XaLibToken(){
};