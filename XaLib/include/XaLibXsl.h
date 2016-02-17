#ifndef XALIBXSL_H
#define XALIBXSL_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;

class XaLibXsl : private XaLibBase {
	private:
		xmlDocPtr res;
		xsltStylesheetPtr cur;

		typedef vector<string> XslParams;

		typedef vector<string> VectorXslParamsName;
		typedef vector<string> VectorXslParamsValue;
		const char* WithParams[32 + 1];

		void AddParams(string XslParamsName, string XslParamsValue,int ParamPosition);
		
	public:
		XaLibXsl(const xmlDocPtr& XmlDoc, const xmlDocPtr& XslDoc,const XslParams& XslParams);

		//[[deprecated("Replaced by XaLibXsl(const xmlDocPtr& XmlDoc, const xmlDocPtr& XslDoc,const XslParams& XslParams), which use vector instead array")]]
        XaLibXsl(xmlDocPtr XmlDoc, xmlDocPtr XslDoc,string XslParams[],int NumElements);

		XaLibXsl(string XmlFilePath, string XslFilePath);
		XaLibXsl(string XmlString, string XslFilePath, int XmlStringSize);
		XaLibXsl(xmlDocPtr doc, string XslFilePath);
		XaLibXsl(xmlDocPtr doc, string XslFilePath,VectorXslParamsName XslParamsName, VectorXslParamsValue XslParamsValue);
		XaLibXsl(xmlDocPtr doc, string XslFilePath,string XslParams[],int NumElements);

		~XaLibXsl();

		string GetXHtml();

	protected:
};

#endif
