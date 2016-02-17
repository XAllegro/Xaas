#include <XaLibBackEndCall.h>

XaLibBackEndCall::XaLibBackEndCall(){
};

string XaLibBackEndCall::BuildCall(const string& Object, const string& Event,const vector <string>& ParamName,const vector <string>& ParamValue){

	string Call=BuildCallBase();

	Call.append("&");
	Call.append("Data=");
	
	string WsData={};
	
	WsData.append("<WsData>");
	
	//ADDING TOKEN
	WsData.append("<login><token>");
	WsData.append(SESSION.Token);
	WsData.append("</token><client_ip>");
	WsData.append(SESSION.ClientIp);
	WsData.append("</client_ip></login>");
	
	//ADDING OPERATION
	WsData.append(BuildCallSectionOperation(Object,Event));
	
	//ADDING PARAMS
	WsData.append(BuildCallSectionParams(ParamName,ParamValue));

	WsData.append("</WsData>");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);

	if (SETTINGS["WsDefaultEncoding"]=="no"){

		XaLibChar LibChar;
		return Call+LibChar.UrlEncode(WsData);

	} else if (SETTINGS["WsDefaultEncoding"]=="B64") {

		return Call+WsData;

	} else {
		
		return Call+WsData;
	
	}
};

string XaLibBackEndCall::BuildCallLogin(const string& Username, const string& Password){

	string Call=BuildCallBase();

	Call.append("&");
	Call.append("Data=");

	//FARE IL CASO CRITTOGRAFATO ED ENCODATO

	string SectionLogin="<WsData><login><username>"+Username+"</username><password>"+Password+"</password></login><operation><object>XaUser</object><event>Login</event></operation></WsData>";
	Call.append(SectionLogin);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);
	return Call;

};

string XaLibBackEndCall::BuildCallBase(){

	if (SETTINGS["WsDefaultReqType"] =="xml") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call Type -> "+SETTINGS["WsDefaultReqType"]);

		string Call="";
		Call.append(SETTINGS["WsDefaultBackEndUrl"]);

		Call.append("?");
		Call.append("ReqType=");
		Call.append(SETTINGS["WsDefaultReqType"]);

		Call.append("&");
		Call.append("Encoding=");
		Call.append(SETTINGS["WsDefaultEncoding"]);

		Call.append("&");
		Call.append("Encryption=");
		Call.append(SETTINGS["WsDefaultEncryption"]);

		Call.append("&");
		Call.append("ResType=");
		Call.append(SETTINGS["WsDefaultResType"]);

		Call.append("&");
		Call.append("ConsumerId=");
		Call.append(SETTINGS["WsConsumerId"]);

		//Call.append("&");
		//Call.append("WsData=");

		
		//FARE IL CASO CRITTOGRAFATO ED ENCODATO

		//&Data=<WsData><login><username>alex@xallegro.com</username><password>ranokkio</password></login><operation><object>XaUser</object><event>Login</event></operation></WsData>

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call -> "+Call);
		return Call;

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"BackEnd Call Type Is Not Supported ->"+SETTINGS["WsDefaultReqType"]);
		throw 201;
	}
};

string XaLibBackEndCall::BuildCallSectionParams(const vector <string>& ParamName,const vector <string>& ParamValue){

	string ParamSection="<params>";
	
	if (ParamName.size()!=ParamValue.size()) {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Parameters and Values Have Different Size");
		throw 202;
	
	} else if(ParamName.size()==0){
		
		ParamSection.append("<p><n></n><v></v></p>");

	} else {
		
		for (auto i=0; i<ParamName.size(); i++) {

			ParamSection.append("<p><n>");

			ParamSection.append(ParamName[i]);
			ParamSection.append("</n><v>");

			ParamSection.append(ParamValue[i]);
			ParamSection.append("</v></p>");
		}
	}

	ParamSection.append("</params>");

	return ParamSection;
};

string XaLibBackEndCall::BuildCallSectionOperation(const string& Object, const string& Event){

	string SectionOperation="<operation><object>"+Object+"</object><event>"+Event+"</event></operation>";
	return SectionOperation;
};

XaLibBackEndCall::~XaLibBackEndCall(){
};