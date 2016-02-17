#include <XaLibXsl.h>
#include <XaLibBase.h>

XaLibXsl::XaLibXsl(const xmlDocPtr& XmlDoc, const xmlDocPtr& XslDoc,const XslParams& XslParams){

	int NumElements=XslParams.size();
	cur = NULL;
	*WithParams = NULL;
	string ParamName;
	string ParamValue;

	if(NumElements>0) {

		for(int n=0; n<NumElements; n=n+2) {

			ParamName=XslParams[n];
			ParamValue=XslParams[n+1];
			this->AddParams(ParamName,ParamValue,n);
	    }

		WithParams[NumElements] = NULL;

	} else {

		string strWithParamName="";
		strWithParamName.append("'NoParamName'");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = NULL;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

    cur = xsltParseStylesheetDoc(XslDoc);
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, XmlDoc, WithParams);
	xmlFreeDoc(XmlDoc);

	*WithParams = NULL;
};

//DEPRECATED
XaLibXsl::XaLibXsl(xmlDocPtr XmlDoc, xmlDocPtr XslDoc, string XslParams[], int NumElements){

	cur = NULL;
	*WithParams = NULL;
	string ParamName;
	string ParamValue;

	if(NumElements>0) {

		for(int n=0; n<NumElements; n=n+2) {

			ParamName=XslParams[n];
			ParamValue=XslParams[n+1];
			this->AddParams(ParamName,ParamValue,n);
	    }

		WithParams[NumElements] = NULL;

	} else {

		string strWithParamName="";
		strWithParamName.append("'NoParamName'");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = NULL;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

    cur = xsltParseStylesheetDoc(XslDoc);
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, XmlDoc, WithParams);
	xmlFreeDoc(XmlDoc);

	*WithParams = NULL;
};

XaLibXsl::XaLibXsl(string XmlFilePath, string XslFilePath){

	xmlDocPtr doc;

	const char *NoParams[1];
	NoParams[0] = 0;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;
	
	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	char *docname = (char*)XmlFilePath.c_str();
	doc = xmlReadFile(docname,NULL,0);

	res = xsltApplyStylesheet(cur, doc, NoParams);
	xmlFreeDoc(doc);
	
	*NoParams = NULL;
	
};

XaLibXsl::XaLibXsl(string XmlString, string XslFilePath, int XmlStringSize){

	const char *XmlChar = (char*)XmlString.c_str();
	xmlDocPtr doc;

	const char *params[16 + 1];

	string strParam="";
		strParam.append("NoParamName");
		const char *chrParam = (char*)strParam.c_str();

		string strValue="";
		strValue.append("'NoParamValue'");
		const char *chrValue = (char*)strValue.c_str();
		
		params[0] = chrParam;
		params[1] = chrValue;
		params[2] = NULL;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	doc = xmlRecoverMemory(XmlChar,XmlStringSize);
	res = xsltApplyStylesheet(cur, doc, params);
};


XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath){

	const char *NoParams[1];
	NoParams[0] = 0;

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, doc, NoParams);
	xmlFreeDoc(doc);

};


XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath,string XslParams[],int NumElements){

	cur = NULL;
	*WithParams = NULL;
	string ParamName;
	string ParamValue;

	if(NumElements>0) {

		for(int n=0; n<NumElements; n=n+2) {

			ParamName=XslParams[n];
			ParamValue=XslParams[n+1];
			this->AddParams(ParamName,ParamValue,n);
	    }

		WithParams[NumElements] = NULL;

	} else {

		string strWithParamName="";
		strWithParamName.append("NoParamName");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = NULL;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, doc, WithParams);
	xmlFreeDoc(doc);

	*WithParams = NULL;
};

XaLibXsl::XaLibXsl(xmlDocPtr doc, string XslFilePath,VectorXslParamsName XslParamsName, VectorXslParamsValue XslParamsValue){

	cur = NULL;
	*WithParams = NULL;

	unsigned XslParamsNameSize=XslParamsName.size();
	unsigned XslParamsValueSize=XslParamsValue.size();

	if(XslParamsNameSize==XslParamsValueSize && XslParamsNameSize>0) {
		
		int j=0;

		for(int n=0; n<XslParamsValueSize; n++) {

			string pippo=XslParamsName.at(n).c_str();
			string pluto=XslParamsValue.at(n).c_str();
			
			this->AddParams(pippo,pluto,j);
			j=j+2;
	    }

		WithParams[j] = 0;

	} else {

		string strWithParamName="";
		strWithParamName.append("NoParamName");

		string strWithParamValue="";
		strWithParamValue.append("'NoParamValue'");
		
		WithParams[0] = (char*)strWithParamName.c_str();
		WithParams[1] = (char*)strWithParamValue.c_str();
		WithParams[2] = 0;
	}

	xmlSubstituteEntitiesDefault(1);
	xmlLoadExtDtdDefaultValue = 1;

	cur = xsltParseStylesheetFile((const xmlChar *)XslFilePath.c_str());
	exsltRegisterAll();

	res = xsltApplyStylesheet(cur, doc, WithParams);
	xmlFreeDoc(doc);

	*WithParams = NULL;

};

void XaLibXsl::AddParams(string XslParamsName, string XslParamsValue,int ParamPosition){

	string strWithParamName="";
	string strWithParamValue="";
	int j=ParamPosition;


	strWithParamName.append(XslParamsName.c_str());
	
	strWithParamValue.append("'");
	strWithParamValue.append(XslParamsValue.c_str());
	strWithParamValue.append("'");

	char* s = new char[strWithParamName.length()+1];
	strcpy(s,strWithParamName.c_str());

	char* t = new char[strWithParamValue.length()+1];
	strcpy(t,strWithParamValue.c_str());


	WithParams[j] = s;
	WithParams[j+1] =t;

};

string XaLibXsl::GetXHtml(){

	xmlChar *out=0;
	int len = 9999;

	if( xsltSaveResultToString(&out,&len, res, cur)==0) {

		out[len] = 0;

		xsltFreeStylesheet(cur);
		xmlFreeDoc(res);

		xsltCleanupGlobals();
		xmlCleanupParser();

	} else {

		cout<<"errore parsing"<<endl;
	}

	char* XHtmlChr=(char*)out;

	if( *XHtmlChr==0){

		return "Error XmlOutput";

	} else {

		string Form=FromCharArrayToString(XHtmlChr);
		//LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Generated Xhtml -> "+Form);
		return Form;

	}
};

XaLibXsl::~XaLibXsl(){
};