#include <XaLibError.h>

XaLibError::XaLibError(){
};

string XaLibError::GetError(const int& ErrorCode) {

	Setup();
	return XaErrors[ErrorCode];
};

void XaLibError::Setup() {

	
	/*
	 *  DB
	 */
	XaErrors[21]={"LOG Unable to open Log file"};
	XaErrors[22]={"DB Unable to Connect SESSION DB"};
	XaErrors[23]={"DB Unable to Connect WRITE DB"};
	XaErrors[24]={"DB Unable to Connect READ DB"};
	XaErrors[25]={"DB Unable to Connect LOG DB"};
	
	XaErrors[28]={"DB Error Executing QRY"};

	
	XaErrors[31]={"Number Of Labels Is different From Number Of Values"};
	
	XaErrors[41]={"Event Is empty"};
	XaErrors[42]={"EventNotFound"};

	XaErrors[45]={"User Does Not Exist Or Password Is Wrong"};
	XaErrors[46]={"User Is Not Unique"};
	XaErrors[47]={"Username Or Password Is Empty"};

	/*
	 * Security
	 */
	XaErrors[51]={"TOKEN Error Inserting a new TOKEN into database"};
	XaErrors[52]={"TOKEN is not valid"};
	XaErrors[53]={"TOKEN Error Deactivating Token For User Id"};
	XaErrors[54]={"TOKEN More tokens are associated to this User or more users have this token"};
	XaErrors[55]={"TOKEN Error Deactivating Token"};
	XaErrors[56]={};
	XaErrors[57]={};

	
	/*
	 * Web Services
	 */
	XaErrors[101]={"WS Requested Without XmlData Parameter"};
	XaErrors[102]={"WS Requested Without ReqType Parameter"};
	XaErrors[103]={"WS Requested Without Encoding Parameter"};
	XaErrors[104]={"WS Requested Without Encryption Parameter"};
	XaErrors[105]={"WS Requested Without ConsumerId Parameter"};
	XaErrors[106]={"WS Requested Without ResType Parameter"};

	XaErrors[107]={"WS Requested Encrypted But No Encoded"};
	XaErrors[108]={};//GetEncodedData
	XaErrors[109]={"WS Requested Encoding Is Not Supported"};
	XaErrors[110]={"WS ConsumerId Is Invalid"};
	XaErrors[111]={""};//GetDecryptedData
	XaErrors[112]={"WS Username Is Empty"};
	XaErrors[113]={"WS Password Is Empty"};
	XaErrors[114]={"WS Object Is Empty"};
	XaErrors[115]={"WS Event Is Empty"};
	XaErrors[116]={"WS Number of Parameters is 0"};
	XaErrors[117]={"WS Object Is Not XaUserLogin But Token is Empty"};
	XaErrors[118]={"WS Event Is Not Login But Token is Empty"};
	XaErrors[119]={"WS Called Object Does Not Exist"};
	XaErrors[120]={"WS Consumer IP or Consumer Host Name are not valid"};
	XaErrors[121]={""};
	XaErrors[122]={""};
	XaErrors[123]={""};

	/*
	 * Action and Model
	 */
	XaErrors[201]={"BackEnd Call Type Is Not Supported"};
	XaErrors[202]={"Parameters and Values Have Different Size"};
	XaErrors[203]={"Requested XML File Does Not Exist"};
	XaErrors[204]={"Requested HTML File Does Not Exist"};
	XaErrors[205]={"Required Parameter is missing"};
	XaErrors[206]={"Searched Element Is Not Present in The Vector"};
	
	
	
	/*
	 * Action Databases
	 */
	
	XaErrors[301]={"Error inserting a new record into the database"};
	XaErrors[302]={"Requested record does not exist into database"};
	XaErrors[303]={"Record already exists into database"};
	XaErrors[304]={"Record is not unique"};

	/*Front End Errors*/
	XaErrors[611]={"Requested Object Does Not Exist"};
	XaErrors[612]={"Requested Event Does Not Exist"};

	
	XaErrors[621]={"Event Is empty"};

	/*
	 * CURL
	 */
	
	XaErrors[701]={"CURL Error Performing Request"};
	
	
	/*
	 * Http Cookie Session
	 */
	XaErrors[801]={"Error Creating Cookie"};
	
};

XaLibError::~XaLibError(){
};