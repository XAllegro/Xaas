#include <XaLibController.h>

/**
 *Super Global Variables
*/
XaLibLog LOG;
XaLibHttp HTTP;
XaLibDb DB_SESSION;
XaLibDb DB_READ;
XaLibDb DB_WRITE;
XaLibDb DB_LOG;

//XaSession SESSION;
unique_ptr<ofstream> MY_LOG_FILE;

XaSettings SETTINGS;
XaRequest REQUEST;
XaResponse RESPONSE;
XaSession SESSION;

XaLibController::XaLibController() {
};

void XaLibController::LoadXmlConfFile(string ConfFile){

	unique_ptr<XaLibConfig> LibConfig(new XaLibConfig());
	LibConfig->GetParams(ConfFile);
};

void XaLibController::StartLog(){

	if (SETTINGS["LogUseDb"]=="yes" && SETTINGS["DatabaseEnable"]=="yes") {

		MY_LOG_FILE.reset(nullptr);

	} else {

		MY_LOG_FILE.reset(new ofstream((char*)(SETTINGS["LogDir"]+SETTINGS["LogFile"]).c_str(), ios::out | ios::app));

		if (MY_LOG_FILE.get()->is_open()){

		} else {

			throw 21;
		}
	}
};

void XaLibController::StartHttp(){

	REQUEST.HeadersString=HTTP.GetHttpHeadersString();
};

void XaLibController::StartDb(){

	vector<string> DbTypeName = {"","Write","Read","Session","Log"};

	if (SETTINGS["DatabaseEnable"]=="yes") {

		if (DB_SESSION.Connect(3)==0) {
			throw 22;
		}

		/* Multiple Databases Configuration*/
		if (SETTINGS["DatabaseEnableMulti"]=="yes") {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Databases Multi Configuration Enabled");
			
			if (DB_WRITE.Connect(1)==0) {
				throw 23;
			}

			if (DB_READ.Connect(2)==0) {
				throw 24;
			}

			if (DB_LOG.Connect(4)==0) {
				throw 25;
			}

		/* Single Database Configuration*/
		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Databases Multi Configuration Disabled");

			DB_WRITE=DB_SESSION;
			DB_READ=DB_SESSION;
			DB_LOG=DB_SESSION;
		}

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Databases Enabled");

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Databases Disabled");
	}
};

void XaLibController::SendHeaders (const string& HeadersType) {
	
	
	//cout<<HTTP.SetCookie()<<endl;

	if (HeadersType=="location") {

		cout<<"Location: ?"+RESPONSE.Location<<endl;
		cout<< "Content-Type: text/html; charset=utf-8\n\n";
	
	} else if (HeadersType=="html" || HeadersType=="xhtml" || HeadersType=="NoHttpParam") {

		cout<< "Content-Type: text/html; charset=utf-8\n\n";

	} else if (HeadersType=="txt") {

		cout<< "Content-Type: text/plain\n\n";

	} else if (HeadersType=="xml") {

		cout<< "Content-Type: text/xml\n\n";

	} else {

		cout<< "Content-Type: text/html; charset=utf-8\n\n";
	}
};

XaLibController::~XaLibController() {
};