#include <XaLibGui.h>

XaLibGui::XaLibGui(){
};

string XaLibGui::CreateList(DbResMap ResMap,const vector<string>& TagNames,const string& RootTagName,const string& GroupTagName) {

	string Result={""};

	if (ResMap[0].size()!=TagNames.size()) {
		
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"TagNames and ResMap sizes are different");

	} else {

		Result.append("<" +RootTagName + ">");

		for (auto i=0;i<ResMap.size();i++) {

			Result.append("<" +GroupTagName + ">");

			for (auto j=0;j<TagNames.size();j++) {

				Result.append("<"+TagNames[j]+">" +ResMap[i][TagNames[j]]+ "</"+TagNames[j]+">");
			}

			Result.append("</" +GroupTagName + ">");
		};

		Result.append("</" +RootTagName + ">");
	
	};

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Assembled XML -> "+Result);

	return Result;
};

string XaLibGui::CreateForm(const vector<string>& XmlFiles, const vector<string>& XmlStrings,const vector<string>& XslFiles,const vector<string>& XslStrings,const vector<string>& XslParams){

	xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(XmlFiles,XmlStrings,1);
	xmlDocPtr XslDomDoc=XaLibDom::DomFromStringAndFile(XslFiles,XslStrings,2);

	unique_ptr<XaLibXsl> LibXsl (new XaLibXsl(XmlDomDoc,XslDomDoc,XslParams));

	return LibXsl->GetXHtml();;

};


XaLibGui::~XaLibGui(){
};