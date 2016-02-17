#include <XaUserLogin.h>

XaUserLogin::XaUserLogin(){
};

void XaUserLogin::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Login"){

        this->Login();

    } else if (CalledEvent=="Logout"){

		this->Logout();

    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}

};

/*TEST CASE
 TUTTE LE COMBINAZIONI
 */
void XaUserLogin::Login (){

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
};

XaUserLogin::~XaUserLogin(){
};