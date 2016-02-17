#include <XaLibBase.h>

#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <fstream>
#include <stdexcept>
#include <new>
#include <algorithm>
#include <time.h>
#include <assert.h>
#include <thread>
#include <future>
#include <unistd.h>
#include <iomanip>
#include <memory>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <openssl/sha.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/conf.h>

using namespace std;

XaLibBase::XaLibBase(){

};

int XaLibBase::PositionInVector(vector<string>& SearchOn,const string& SearchFor) {

	int pos = find(SearchOn.begin(), SearchOn.end(), SearchFor) - SearchOn.begin();
	
	if(pos >= SearchOn.size()) {
		pos=-1;
	}

	return pos;
}; 

string XaLibBase::FromIntToString(int IntValue){

	return to_string(IntValue);
};

int XaLibBase::FromStringToInt(const string& StringValue){

	return atoi(StringValue.c_str());
};

unsigned int XaLibBase::FromHexStringToUnsignedInt(string StringValue){
	
	unsigned int IntValue;   
	stringstream ss;
	ss << hex << StringValue;
	ss >> IntValue;

	return IntValue;
};

string XaLibBase::FromFloatToString(float FloatValue){

	return to_string(FloatValue);
};

float XaLibBase::FromStringToFloat(string StringValue){

	return atof(StringValue.c_str());
};


string XaLibBase::FromDoubleToString(double DoubleValue){

	return to_string(DoubleValue);
};

double XaLibBase::FromStringToDouble(string StringValue){

	return atof(StringValue.c_str());
};

string XaLibBase::FromCharToString(char CharValue){
	
	stringstream ssStream;
	ssStream << CharValue;
	string StringValue = ssStream.str();

	return StringValue;
};

string XaLibBase::FromCharArrayToString(char CharValue[]){
	
	string StringValue(CharValue);

	return StringValue;
};

char* XaLibBase::FromStringToCharArray(string StringValue){

	int StringSize=StringValue.size();

	char* CharValue = new char[StringSize+1];

	for (int i=0;i<=StringSize;i++) {
		CharValue[i]=StringValue[i];
	}

	return CharValue;
};

string XaLibBase::FromStringToHex(const string& StringValue,int CapitalCase){

    static const char* const lut = "0123456789ABCDEF";
    size_t len = StringValue.length();

	string HexString;
    HexString.reserve(2 * len);

    for (size_t i = 0; i < len; ++i) {

        const unsigned char c = StringValue[i];
        HexString.push_back(lut[c >> 4]);
        HexString.push_back(lut[c & 15]);
    }
	
	
	return HexString;
	
	/*
	stringstream str;
	str << StringValue;

	string HexValue;
	str >> hex >> HexValue;
	return HexValue;*/
};

int XaLibBase::FromCharToInt(char CharValue){

	int IntValue= CharValue-48;

	return IntValue;
};

vector<string> XaLibBase::FromCsvStringToVector(string& CsvString){

	//TODO:CHECK THE STRING: LOOP RISK
	CsvString.append(",");

	vector <string> Elements;
 
	unsigned pos=CsvString.find_first_of(",");

	while (pos!=-1) {

		Elements.push_back(CsvString.substr(0,pos));
		CsvString.erase(0,pos+1);
		pos=CsvString.find_first_of(",");
	}

	return Elements;
};

void XaLibBase::SendHtmlHeaders(){

	cout<< "Content-Type: text/html; charset=utf-8\n\n";
};

XaLibBase::~XaLibBase(){
};
