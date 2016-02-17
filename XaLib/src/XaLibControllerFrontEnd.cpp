#include <XaLibControllerFrontEnd.h>

XaLibControllerFrontEnd::XaLibControllerFrontEnd() {
};

void XaLibControllerFrontEnd::OnStart(const string& ConfFile) {

	try {

		LoadXmlConfFile(ConfFile);
		StartLog();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"########################### STARTING FRONT END ACTION LOG ############################");

		//StartDb();
		StartHttp();

		//GetServerInfo();
		//GetClientInfo();
		SESSION.FrontEndIp=HTTP.GetServerIpAddress();
		SESSION.ClientIp=HTTP.GetClientIpAddress();
		GetLayout();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Client-> "+SESSION.ClientIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ip Address Front End Server -> "+SESSION.FrontEndIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " + REQUEST.HeadersString);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Language -> "+REQUEST.Language);
//		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Request Device -> "+REQUEST.Device);

		//RESPONSE.ResponseType=REQUEST.ResponseType;

	} catch (int e) {

		throw;
	}
};

void XaLibControllerFrontEnd::GetLayout(){

	REQUEST.CalledLayout=HTTP.GetHttpParam("lay");
};

void XaLibControllerFrontEnd::ManageSession(){

	if (REQUEST.CalledObject=="XaUserLoginUi" && REQUEST.CalledEvent=="Login") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Setting Cookie");
		cout<<HTTP.SetCookie()<<endl;

	} else if (REQUEST.CalledObject=="XaUserLoginUi" && REQUEST.CalledEvent=="Logout") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Removing Cookie");
		cout<<HTTP.RemoveCookie()<<endl;
	}
};

void XaLibControllerFrontEnd::SendResponse() {

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Sending Response Page Content -> " +RESPONSE.Content);
	SendHeaders(RESPONSE.ResponseType);
	cout<<RESPONSE.Content<<endl;
};

/*
void XaLibController::GetServerInfo(){

	REQUEST.ServerIpAddress=HTTP.GetServerIpAddress();
};
*/
/*
void XaLibController::GetCall(){

	REQUEST.CalledObject=HTTP.GetHttpParam("obj");
	REQUEST.CalledEvent=HTTP.GetHttpParam("evt");
};

void XaLibController::GetWs(){

	REQUEST.WsXml=HTTP.GetHttpParam("WsXml");
	REQUEST.WsXmlDataEncoding=HTTP.GetHttpParam("Encoding");
	REQUEST.WsXmlDataKey=HTTP.GetHttpParam("WsKey");
	REQUEST.WsXmlDataIV=HTTP.GetHttpParam("WsIV");

	string WsXmlData=HTTP.GetHttpParam("WsXmlData");

	if (REQUEST.WsXmlDataEncoding=="B64") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ws B64 Encoded String -> "+ WsXmlData);

		unique_ptr<XaLibChar> LibChar(new XaLibChar());
		string WsXmlDataDecoded=LibChar->B64Decode(WsXmlData);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ws B64 Decoded String -> "+ WsXmlDataDecoded);
		WsXmlData=WsXmlDataDecoded;

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ws Unencoded String -> "+ WsXmlData);
	}

	if (REQUEST.WsXmlDataKey!="NoHttpParam" && REQUEST.WsXmlDataKey!="" && REQUEST.WsXmlDataIV!="NoHttpParam" && REQUEST.WsXmlDataIV!="") {
		if (REQUEST.WsXmlDataKey.length()==64 && REQUEST.WsXmlDataIV.length()==32) {

			XaLibCrypto* LibCrypto=new XaLibCrypto();
			string WsXmlDataDecrypted=LibCrypto->AesDecryptCtr(WsXmlData,REQUEST.WsXmlDataKey,REQUEST.WsXmlDataIV);

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Ws AES 256 CTR Decrypted String -> "+ WsXmlDataDecrypted);
			REQUEST.WsXmlData=WsXmlDataDecrypted;

		} else {
			if (REQUEST.WsXmlDataKey.length()!=64) { LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Wrong WsKey length (should be 64) -> "+XaLibBase::FromIntToString(REQUEST.WsXmlDataKey.length()) ); };
			if (REQUEST.WsXmlDataIV.length()!=32)  { LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Wrong WsIV length (should be 32) -> "+XaLibBase::FromIntToString(REQUEST.WsXmlDataIV.length()) ); };
			//RESPONSE.Content="<WsXmlData><error>Incorrect Length of Encryption Key and/or Initialization Vector</error></WsXmlData>";
			//SendResponse();

		}
	} else {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Uncoded String -> "+ WsXmlData);
		REQUEST.WsXmlData=WsXmlData;
	}
	
};

int XaLibController::ProfileCalledObject(const string& CalledObject,const string& CalledEvent){

	int ReturnStatus=0;

	XaUserProfile UserProfile;

	if (UserProfile.EventIsFree(CalledObject,CalledEvent)==1){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access FREE -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		ReturnStatus=1;

	} else {

		if(UserProfile.EventProfile(CalledObject,CalledEvent)==1){

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Granted Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
			ReturnStatus=1;

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"REFUSED Access -> Object:="+CalledObject+" :: Event:="+CalledEvent);
		}
	}

	return ReturnStatus;
};

void XaLibController::DispatchWs() {

	if(SETTINGS["WsEnable"]=="yes" && SETTINGS["WsEnable"]!="" && SETTINGS["WsEnable"]!="NoHttpParam"){
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Enabled");

		if (REQUEST.WsXmlData!="" && REQUEST.WsXmlData!="NoHttpParam") {

			string WsHttpHeaders="";

			unique_ptr<XaLibDom> LibDom(new XaLibDom());
			xmlDocPtr XmlDomDoc=LibDom->DomFromString(REQUEST.WsXmlData);

			REQUEST.WsXmlUsername=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/login/password");
			REQUEST.WsXmlPassword=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/login/username");
			
			REQUEST.WsCallerName=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/caller/name");
			REQUEST.WsCallerKey=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/caller/key");

			XaWs Ws;
			if (Ws.CheckCaller(REQUEST.WsCallerName,REQUEST.WsCallerKey)==1) {

				string WsXmlLanguage=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/language");

				if (WsXmlLanguage!="" && WsXmlLanguage!="NoHttpParam" && WsXmlLanguage!="ERROR-ELEMENT-NOT-DEFINED") {
					REQUEST.Language=WsXmlLanguage;
				}
	
				REQUEST.CalledObject=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/operation/object");
				REQUEST.CalledEvent=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/operation/event");

				unique_ptr<XaUser> User(new XaUser());
				REQUEST.XaUser_ID=User->Authenticate(REQUEST.WsXmlUsername,REQUEST.WsXmlPassword);

				if(REQUEST.XaUser_ID!=0) {

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS User Authenticated With Username ->" + REQUEST.WsXmlUsername);	

					WsHttpHeaders.append("&obj="+REQUEST.CalledObject+"&evt="+REQUEST.CalledEvent);

					//CALCOLO IL NUMERO DEI PARAMETRI
					int ParamsNum=LibDom->GetNumRowByXPathInt(XmlDomDoc,"/WsXmlData/params/param");

					if (ParamsNum==0){

						LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Number of Parameters is 0");
						RESPONSE.Content="<WsXmlData><error>There are not parameters in the request</error></WsXmlData>";
						SendResponse();

					} else {

						LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Number of Parameters ->" + XaLibBase::FromIntToString(ParamsNum));

						for (int i=0;i<ParamsNum;i++) {

							string ParamName =LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/params/param["+ XaLibBase::FromIntToString(i+1) + "]/name");
							string ParamValue=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsXmlData/params/param["+ XaLibBase::FromIntToString(i+1) + "]/value");

							LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Read Parameter ->" +ParamName +" :: With Value -> "+ParamValue);
							WsHttpHeaders.append("&"+ParamName+"="+ParamValue);
						}

						vector<string> VectorFields{"XaUser_ID","caller","object","event","request","request_time"};
						vector<string> VectorValues{XaLibBase::FromIntToString(REQUEST.XaUser_ID),REQUEST.WsCallerName,REQUEST.CalledObject,REQUEST.CalledEvent,REQUEST.WsXmlData,XaLibTime::GetDateTimeMySql()};

						unique_ptr<XaLibSql> LibSql(new XaLibSql());
						REQUEST.XaWsSession_ID=LibSql->Insert(DB_SESSION,"XaSessionWsLog",VectorFields,VectorValues);

						VectorFields.clear();
						VectorValues.clear();
					}

					LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Composed HTTP String -> " + WsHttpHeaders);

					REQUEST.HeadersString=WsHttpHeaders+"&XaSessionWsLog_ID="+XaLibBase::FromIntToString(REQUEST.XaWsSession_ID);

					if (REQUEST.CalledObject!="NoHttpParam" && REQUEST.CalledObject!="" && REQUEST.CalledEvent!="NoHttpParam" && REQUEST.CalledEvent!="") {

						if (XaLibController::ProfileCalledObject(REQUEST.CalledObject,REQUEST.CalledEvent)==1){

							this->ExecuteCalledObject();

						} else {

							LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS Not Profiled Object-Event -> "+REQUEST.CalledObject+"::"+REQUEST.CalledEvent);
							RESPONSE.Content="<WsXmlData><error>User Not Authorized To Execute Action Or Action Does Not Exist: "+REQUEST.CalledObject+"::"+ REQUEST.CalledEvent +"</error></WsXmlData>";
							SendResponse();
						}

					} else {

						RESPONSE.Content="<WsXmlData><error>Missing Object or Event</error></WsXmlData>";
						SendResponse();
					}

				} else {

					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS User Rejected With Username And Password-> "+ REQUEST.WsXmlUsername+ " :: "+REQUEST.WsXmlPassword);
					RESPONSE.Content="<WsXmlData><error>Username Or Password Error</error></WsXmlData>"	;
					SendResponse();
				}
				
			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"WS User Caller Rejected With WsCallerName And WsCallerKey-> "+ REQUEST.WsCallerName+ " :: "+REQUEST.WsCallerKey);
				RESPONSE.Content="<WsXmlData><error>Caller Name or Caller Key Error</error></WsXmlData>"	;
				SendResponse();
			}

		} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS POST Without Xml Data");
			RESPONSE.Content="<WsXmlData><error>POST Without Xml Data</error></WsXmlData>";
			SendResponse();
		}

	} else {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"WS Disabled");
			RESPONSE.Content="<WsXmlData><error>WS Are Disabled On This Server</error></WsXmlData>";
			SendResponse();
	}
		
	
};

void XaLibController::Dispatch() {

	if (REQUEST.CalledObject!="NoHttpParam" && REQUEST.CalledObject!="" && REQUEST.CalledEvent!="NoHttpParam" && REQUEST.CalledEvent!="") {

		if (SETTINGS["AccessControl"]!="no") {

			if (ProfileCalledObject(REQUEST.CalledObject,REQUEST.CalledEvent)==1){

				if (REQUEST.HeadersString!="") {

					REQUEST.HeadersString+=REQUEST.HeadersStringCustom;

				} else {

					REQUEST.HeadersString+="?"+REQUEST.HeadersStringCustom;
				}

				this->ExecuteCalledObject();

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Not Profiled Object-Event -> "+REQUEST.CalledObject+"::"+REQUEST.CalledEvent);
				
				RESPONSE.Object="XaPages";
				RESPONSE.Event="XaInfoPage";
				RESPONSE.Headers="&ErrorMessage=EventNotProfiled";
				
				this->Dispatch();

			}

		} else if(SETTINGS["AccessControl"]=="no") {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"+++ ACCESS CONTROL DISABLED +++");
			
			if (REQUEST.HeadersString!="") {

					REQUEST.HeadersString+=REQUEST.HeadersStringCustom;

				} else {

					REQUEST.HeadersString+="?"+REQUEST.HeadersStringCustom;
				}

			this->ExecuteCalledObject();
		}

    } else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Default Object -> "+ REQUEST.CalledObject=SETTINGS["DefaultObject"] + " And Default Event -> " +REQUEST.CalledEvent=SETTINGS["DefaultEvent"]);

		//GESTIRE SE SONO NULLI SETTINGS["DefaultObject"] e SETTINGS["DefaultEvent"];
		REQUEST.CalledObject=SETTINGS["DefaultObject"];
		REQUEST.CalledEvent=SETTINGS["DefaultEvent"];
		this->ExecuteCalledObject();
    }
};

void XaLibController::ExecuteCalledObject() {};
		
void XaLibController::SendResponse(){
	
	if (RESPONSE.Object!="" && RESPONSE.Event!="") {

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Calling PostObject ->"+RESPONSE.Object+ ":: With PostEvent ->"+RESPONSE.Event);
	
		REQUEST.CalledObject=RESPONSE.Object;
		REQUEST.CalledEvent=RESPONSE.Event;
		REQUEST.HeadersStringCustom=RESPONSE.Headers;

		RESPONSE.Object="";
		RESPONSE.Event="";

		Dispatch();

	} else {

		//LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Sending Page Content -> " +RESPONSE.Content);
		SendHeaders(RESPONSE.ResponseType);
		cout<<RESPONSE.Content<<endl;

	}
};

void XaLibController::SendHeaders (string& HeadersType) const {

	if (HeadersType=="html" || HeadersType=="xhtml") {
		
		cout<< "Content-Type: text/html; charset=utf-8\n\n";
	
	} else if (HeadersType=="txt") {
	
		cout<< "Content-Type: text/plain\n\n";
	
	} else if (HeadersType=="xml") {
	
		cout<< "Content-Type: text/xml\n\n";
	
	} else {
		cout<< "Content-Type: text/html; charset=utf-8\n\n";

	}

};

void XaLibController::SendLocationHeaders(string Location){

	cout<<"Location: ?"+Location<<endl;
	cout<< "Content-Type: text/html; charset=utf-8\n\n";

};
*/
XaLibControllerFrontEnd::~XaLibControllerFrontEnd() {
};