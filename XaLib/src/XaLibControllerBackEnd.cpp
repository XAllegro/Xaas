#include <XaLibControllerBackEnd.h>

XaLibControllerBackEnd::XaLibControllerBackEnd() {
};

void XaLibControllerBackEnd::OnStart(const string& ConfFile) {

	try {

		LoadXmlConfFile(ConfFile);
		StartLog();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"########################### STARTING BACK END ACTION LOG ############################");

		StartDb();
		StartHttp();

		SESSION.BackEndIp=HTTP.GetServerIpAddress();
		SESSION.FrontEndIp=HTTP.GetClientIpAddress();

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Back End Server -> "+SESSION.BackEndIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"IP Address Front End Server -> "+SESSION.FrontEndIp);
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Read HttpString -> " + REQUEST.HeadersString);

	} catch (int e) {

		throw;
	}
};

void XaLibControllerBackEnd::SendResponse(){

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"RESPONSE="+RESPONSE.Content);

		SendHeaders(RESPONSE.ResponseType);

		if (REQUEST.CalledObject=="XaUserLogin" && REQUEST.CalledEvent=="Login") {

			//LOGIN RETURN ALSO THE TOKEN
			if (RESPONSE.ResponseType=="json") {
				
				cout<<"{\"token\":\""+SESSION.Token+"\"}"<<endl;

			} else if (RESPONSE.ResponseType=="xml") {

				cout<<"<WsData><token>"+SESSION.Token+"</token>"+RESPONSE.Content+"</WsData>"<<endl;
			}

		} else {

			if (RESPONSE.ResponseType=="json") {

				cout<<"{"+RESPONSE.Content+"}"<<endl;

			} else if (RESPONSE.ResponseType=="xml") {

				cout<<"<WsData>"+RESPONSE.Content+"</WsData>"<<endl;
			}
		}	
};

XaLibControllerBackEnd::~XaLibControllerBackEnd() {
};