#include <XaUserLogin.h>

XaUserLogin::XaUserLogin(){
};

void XaUserLogin::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Login"){

        this->Login();

    } else if (CalledEvent=="Logout"){

		this->Logout();

    } else if (CalledEvent=="ReadByToken"){

		this->ReadByToken();

    } else if (CalledEvent=="ChangePassword"){

		this->ChangePassword();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}

};

/*TEST CASE
 TUTTE LE COMBINAZIONI
 */
void XaUserLogin::Login () {

	string StrUsername=HTTP.GetHttpParam("username");
	string StrPassword=HTTP.GetHttpParam("password");

	if (StrUsername !="" && StrPassword !="") {

		string ShaPassword=XaLibCrypto::GetSha1(StrPassword);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"USER Encrypted Password -> "+ShaPassword);
		
		string SqlQry="SELECT id FROM XaUser WHERE username=\""+StrUsername+"\" AND password=\""+ShaPassword+"\" AND status in (0,1)";
		DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

		int n=DbRes.size();

		if (n==0) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-45: USER Does Not Exist Or The Password Is Wrong -> " + StrUsername);
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

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-46: User Is Not Unique");
			throw 46;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-47: Username Or Password Is Empty");
		throw 47;
	}

};

void XaUserLogin::Logout () {

	XaLibToken::DeactivateUserToken(SESSION.Token);
	
	SESSION.Token="0";
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Logout Affected");
	RESPONSE.Content="Logout";
};


void XaUserLogin::ReadByToken(){

	int XaUser_ID=XaLibToken::ValidateToken(SESSION.Token);
	
	string SqlQry="SELECT name,surname FROM XaUser WHERE status=1 AND id=\""+FromIntToString(XaUser_ID)+"\"";
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

	if (DbRes.size()==1 ){
		
		vector<string> ReturnedFields={"name","surname"};
		RESPONSE.Content=ReadResponse(DbRes,ReturnedFields);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-56: User ID Does Not Exist Or Is not Unique");
		throw 56;
	}

};

void XaUserLogin::ChangePassword() {

	string Password=HTTP.GetHttpParam("password");
	string Password1=HTTP.GetHttpParam("password1");
	string Password2=HTTP.GetHttpParam("password2");

	CheckHttpField({Password,Password1,Password2},"required");

	if (Password1==Password2) {
		
		string QryUser="SELECT id FROM XaUser WHERE id=\""+FromIntToString(SESSION.XaUser_ID)+"\" AND password=\""+XaLibCrypto::GetSha1(Password)+"\" AND status=1";
		DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,QryUser);
		
		int n=DbRes.size();

		if (n==1) {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Old password is correct");
			
			XaLibSql::Update(DB_SESSION,"XaUser",{"password"},{XaLibCrypto::GetSha1(Password1)},{"id"},{FromIntToString(SESSION.XaUser_ID)});

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Password Changed");
			
			RESPONSE.Content="OK";
			
			
		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-58: Old password is not correct");
			throw 58;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-57: New Password and New Password Confirmation are not identical");
		throw 57;
	} 

};

XaUserLogin::~XaUserLogin(){
};