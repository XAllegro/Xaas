#include <XaLibWs.h>
#include <XaLibAction.h>

/*
 CNOTROLLARE SE NEI SETTINGS ABILITATI PLAIN
 */


XaLibWs::XaLibWs() {
};

void XaLibWs::Setup() {

	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Setup");

	ReqType=HTTP.GetHttpParam("ReqType");
	Encoding=HTTP.GetHttpParam("Encoding");
	Encryption=HTTP.GetHttpParam("Encryption");
	ConsumerId=HTTP.GetHttpParam("ConsumerId");
	ResType=HTTP.GetHttpParam("ResType");
	ResLang=HTTP.GetHttpParam("ResLang");
	Data=HTTP.GetHttpParam("Data");

	CheckRequired();

	/*
	* Encrypted - Encoded
	*/
	if (Encryption=="yes") {

		LOG.Write("INF", __FILE__,__FUNCTION__,__LINE__,"WS Requested Encrypted");

		if (Encoding=="no") {

			LOG.Write("ERR", __FILE__,__FUNCTION__,__LINE__,"WS Requested Encrypted But No Encoded");
			throw 107;

		} else {

			LOG.Write("INF", __FILE__,__FUNCTION__,__LINE__,"WS Requested Encrypted And Encoded");
			GetEncodedData();
			GetConsumer();
			GetDecryptedData();
		}

	/*
	* No Encrypted - Encoded
	*/
	} else if(Encryption=="no" && Encoding=="B64") {

		LOG.Write("INF", __FILE__,__FUNCTION__,__LINE__,"WS Requested No Encrypted And Encoded");
		GetEncodedData();
		GetConsumer();

	/*
	* No Encrypted - No Encoded
	*/
	} else if (Encryption=="no" && Encoding=="no") {

		LOG.Write("INF", __FILE__,__FUNCTION__,__LINE__,"WS Requested No Encrypted And No Encoded");
		GetConsumer();
	}

	ExtractData();
	
	if (SETTINGS["WsEnableLog"]=="yes") {

		AddRequestLog();
	}
};

void XaLibWs::CheckRequired() {

	if (Data=="NoHttpParam" || Data=="") {
	
		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without XmlData Parameter");
		throw 101;
	}

	if (ReqType=="NoHttpParam" || ReqType=="") {
	
		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without ReqType Parameter");
		throw 102;
	}

	if (Encoding=="NoHttpParam" || Encoding=="") {
	
		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without Encoding Parameter");
		throw 103;
	}

	if (Encryption=="NoHttpParam" || Encryption=="") {

		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without Encryption Parameter");
		throw 104;
	}

	if (ConsumerId=="NoHttpParam" || ConsumerId=="") {
	
		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without ConsumerId Parameter");
		throw 105;
	}

	if (ResType=="NoHttpParam" || ResType=="") {
	
		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Requested Without ResType Parameter");
		throw 106;
	}
	
	if (ResLang=="NoHttpParam" || ResLang=="") {
	
		ResLang=SETTINGS["DefaultLanguage"];
	};
};

void XaLibWs::GetEncodedData(){

	if (Encoding=="B64") {
			
		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Requested Decode ->" + Encoding);

		unique_ptr<XaLibChar> LibChar(new XaLibChar());
		Data=LibChar->B64Decode(Data);

		//throw 108

	} else {

		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"Ws Requested Encoding Is Not Supported ->" + Encoding);
		Data="";
		throw 109;
	}
};

void XaLibWs::GetConsumer() {

	string SqlQry="SELECT ekey,hostname,ip FROM XaWsConsumer WHERE status=1 and id="+ConsumerId;
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_SESSION,SqlQry);

	if (DbRes.size()==0) {

		LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"Ws ConsumerId Is Invalid -> "+ ConsumerId);
		ConsumerKey="";
		throw 110;

	} else {

		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws ConsumerId Is Valid -> "+ ConsumerId);

		ConsumerKey=DbRes[0]["ekey"];

		//check ip and domain name 
		ConsumerIp=DbRes[0]["ip"];
		ConsumerHostname=DbRes[0]["hostname"];

		/* TODO
			MULTIPLE CASES IP* and HOSTNAME !=* ETC
		*/
		if (ConsumerHostname!="*" || ConsumerIp!="*") {

			//check domain name and Client IP
			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Consumer IP or Consumer Host Name are not valid"+ ConsumerIp+" :: "+ ConsumerHostname);
			throw 120;
		}
	}
};

void XaLibWs::GetDecryptedData() {

	XaLibCrypto* LibCrypto=new XaLibCrypto();
	Data=LibCrypto->AesDecrypt(Data,ConsumerKey);

	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Data -> "+ Data);
	//throw 111;
	//ERRORE EXIT ECC
};

void XaLibWs::AddRequestLog() {

	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Adding Log");
	
	WsId=XaLibSql::Insert(DB_SESSION,"XaWsLog",{"back_end_ip","front_end_ip","client_ip","token","consumer_id","consumer_key","req_type","res_type","encoding","encryption","object","event","data"},
												{SESSION.BackEndIp,SESSION.FrontEndIp,ClientIp,Token,ConsumerId,ConsumerKey,ReqType,ResType,Encoding,Encryption,Object,Event,Data});			
};

void XaLibWs::AddResponseLog() {

	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Updating Log");
	//UPDATE THE LOG WUTH THE RESPONSE
	XaLibSql::Update(DB_SESSION,"XaWsLog",{"response"},{RESPONSE.Content},{"id"},{to_string(WsId)});
};

void XaLibWs::ExtractData(){

	unique_ptr<XaLibDom> LibDom(new XaLibDom());
	xmlDocPtr XmlDomDoc=LibDom->DomFromString(Data);	
	
	//CONTROLLARE CHE LA STRUTTORA SIA GIUSTA XPATH VALIDA
	Username=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/login/username");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Username -> "+ Username);
	
	Password=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/login/password");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Password -> "+ Password);
	
	Token=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/login/token");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Token -> "+ Token);
	
	ClientIp=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/login/client_ip");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws ClientIp -> "+ ClientIp);

	Object=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/operation/object");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Object -> "+ Object);
	
	Event=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/operation/event");
	LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"Ws Event -> "+ Event);

	/*CASE LOGIN*/
	if (Token=="ELEMENT-NOT-DEFINED"){

		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Token Is Empty");

		if (Username=="ELEMENT-NOT-DEFINED") {

			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Username Is Empty");
			throw 112;
		}

		if (Password=="ELEMENT-NOT-DEFINED") {

			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Password Is Empty");
			throw 113;
		}

		if (Object!="XaUserLogin") {

			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Object Is Not XaUserLogin But Token is Empty");
			throw 117;
		}

		if (Event!="Login") {

			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Event Is Not Login But Token is Empty");
			throw 118;
		}

		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Username ->" + Username);
		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Username ->" + Password);

		//Object="XaUser";
		//Event="Login";

	/*CASE TOKEN*/
	} else {

		//FORSE E MEGLIO VERIFICARE CHE USERNAME E PASSWORD NON CI SIANO PROPRIO
		//ESCLUDERE IL CASO CHE SIANO TUTTI E TRE TOKEN USERNAME E PASSWORD
		//O TOKEN O USERNAME E PASSWORD
		//VALIDARE TOKEN

		if(Object=="ELEMENT-NOT-DEFINED") {
			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Object Is Empty");
			throw 114;
		}

		if(Event=="ELEMENT-NOT-DEFINED") {
			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Event Is Empty");
			throw 115;
		}

		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Requested Object ->" + Object);
		LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Requested Event ->" + Event);
		
		int ParamsNum=LibDom->GetNumRowByXPathInt(XmlDomDoc,"/WsData/params/p");

		if (ParamsNum==0){

			LOG.Write("ERR",__FILE__,__FUNCTION__,__LINE__,"WS Number of Parameters is 0");
			throw 116;

		} else {

			LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Number of Parameters ->" + XaLibBase::FromIntToString(ParamsNum));

			/*Adding parameter to the request*/
			for (auto i=0;i<ParamsNum;i++) {

				string ParamName =LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/params/p["+ XaLibBase::FromIntToString(i+1) + "]/n");
				string ParamValue=LibDom->GetElementValueByXPath(XmlDomDoc,"/WsData/params/p["+ XaLibBase::FromIntToString(i+1) + "]/v");
				
				if (ParamValue=="ELEMENT-NOT-DEFINED") {
					ParamValue="NoHttpParam";
				};

				LOG.Write("INF",__FILE__,__FUNCTION__,__LINE__,"WS Adding Parameter ->" +ParamName +" :: With Value -> "+ParamValue);

				//PROBABILMENTE SI PUO SOSTITUIRE CON UGUALE LA VECCHIASTRING NON SERVE PIU
				REQUEST.HeadersString.append("&"+ParamName+"="+ParamValue);
			}
		}
	}
};

string XaLibWs::GetObject() {

	return Object;
};

string XaLibWs::GetEvent() {

	return Event;
};

string XaLibWs::GetUsername() {

	return Username;
};

string XaLibWs::GetPassword() {

	return Password;
};

string XaLibWs::GetToken() {

	return Token;
};

string XaLibWs::GetClientIp() {

	return ClientIp;
};

string XaLibWs::GetResType() {

	return ResType;
};

string XaLibWs::GetResLang() {

	return ResLang;
};

int XaLibWs::GetWsId() {

	return WsId;
};

map <int, map<string,string> > XaLibWs::GetParams() {

	return Params;
};
XaLibWs::~XaLibWs(){
};
