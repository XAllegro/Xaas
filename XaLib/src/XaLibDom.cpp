#include <XaLibDom.h>

#include <XaLibBase.h>
#include <XaLibChar.h>

XaLibDom::XaLibDom(){
};

xmlDocPtr XaLibDom::DomFromFile(string XmlFilePath) {

	xmlDocPtr XmlDomDoc;

	const char *docname = (char*)XmlFilePath.c_str();
	XmlDomDoc = xmlReadFile(docname,NULL,0);

	return XmlDomDoc;
};

xmlDocPtr XaLibDom::DomFromString(string XmlString) {

    xmlDocPtr XmlDomDoc;

	const char *XmlChar = (char*)XmlString.c_str();

	int XmlStringSize=XmlString.size();
	XmlDomDoc = xmlRecoverMemory(XmlChar,XmlStringSize);

	return XmlDomDoc;
};

xmlDocPtr XaLibDom::DomFromFile(const vector<string> XmlFilesPath,const int& AddRootTag) {

	xmlDocPtr XmlDomDoc;
    string XmlStringTotal="";

	if (AddRootTag==1){

        XmlStringTotal.append("<root>");

    }

	//ADDING FILE
    int XmlFilesSize=XmlFilesPath.size();

    if(XmlFilesSize>0) {

		unique_ptr<XaLibChar> LibChar (new XaLibChar());
		   
		for(auto i=0; i<XmlFilesSize; i++) {

			string XmlFilePath=XmlFilesPath.at(i).c_str();
            char* XmlFilePathChar=(char*)XmlFilePath.c_str();

            ifstream MyFile;
            MyFile.open(XmlFilePathChar);

            if (MyFile.is_open()){
 
                string TmpString;

                while(getline(MyFile,TmpString) ) {
					
					XaLibChar::ClearReturn(TmpString);
                    //string TmpStringCleared=LibChar->ClearReturn(TmpString);
                    XmlStringTotal.append(TmpString);
                }

                MyFile.close();

            }
        } 
    }
	
	const char *XmlChar = (char*)XmlStringTotal.c_str();
	int XmlStringSize=XmlStringTotal.size();
	XmlDomDoc = xmlRecoverMemory(XmlChar,XmlStringSize);

	return XmlDomDoc;
};

xmlDocPtr XaLibDom::DomFromStringAndFile(const VectorXmlFilePath& XmlFiles,const VectorXmlString& XmlStrings,const int& AddRootTag) {

	xmlDocPtr XmlDomDoc;
    string XmlStringTotal="";
    
    if (AddRootTag==1){

        XmlStringTotal.append("<root>");

    } else if(AddRootTag==2){

        XmlStringTotal.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
        XmlStringTotal.append("<xsl:stylesheet version=\"1.0\" xmlns:xsl=\"http://www.w3.org/1999/XSL/Transform\">");
        XmlStringTotal.append("<xsl:output method=\"html\" encoding=\"UTF-8\"/>");
    }

    //ADDING FILE
    int XmlFilesSize=XmlFiles.size();

    if(XmlFilesSize>0) {

		unique_ptr<XaLibChar> LibChar (new XaLibChar());
		   
		for(int i=0; i<XmlFilesSize; i++) {

			string XmlFilePath=XmlFiles.at(i).c_str();
            char* XmlFilePathChar=(char*)XmlFilePath.c_str();

            ifstream MyFile;
            MyFile.open(XmlFilePathChar);

            if (MyFile.is_open()){
 
                string TmpString;

                while(getline(MyFile,TmpString) ) {

					XaLibChar::ClearReturn(TmpString);
                    //string TmpStringCleared=LibChar->ClearReturn(TmpString);
                    XmlStringTotal.append(TmpString);
                }

                MyFile.close();

            }
        } 
    }

    //ADDING STRINGS
    int XmlStringsSize=XmlStrings.size();

    if(XmlStringsSize>0) {

		for(int j=0; j<XmlStringsSize; j++) {

			string XmlString=XmlStrings.at(j).c_str();

            XmlStringTotal.append(XmlString);

            }
        }

    if (AddRootTag==1){

        XmlStringTotal.append("</root>");

    } else if(AddRootTag==2){

        XmlStringTotal.append("</xsl:stylesheet>");

    }

	const char *XmlChar = (char*)XmlStringTotal.c_str();
	int XmlStringSize=XmlStringTotal.size();
	XmlDomDoc = xmlRecoverMemory(XmlChar,XmlStringSize);

	return XmlDomDoc;
};

string XaLibDom::StringFromDom(xmlDocPtr XmlDomDoc){

	xmlChar *xmlbuff;
	int buffersize;
			
	xmlDocDumpFormatMemory(XmlDomDoc, &xmlbuff, &buffersize, 1);

	ostringstream ss;
	ss << xmlbuff;
	string XmlTrunc=ss.str();
	xmlFree(xmlbuff);

	string ToSearch="<?xml version=\"1.0\"?>";
	unsigned posFrom=XmlTrunc.find("<?xml version=\"1.0\"?>");

	if (posFrom!=-1){
		
		unsigned posSize=ToSearch.size();
		XmlTrunc.erase (posFrom,posSize);
	}

	return XmlTrunc;
}


string XaLibDom::GetRootValue(xmlDocPtr XmlDomDoc) {
	
	xmlNodePtr CurNode;
	const xmlChar* CurNodeName;
	string stringValue="";

	CurNode = xmlDocGetRootElement(XmlDomDoc);
	if (CurNode!=NULL) {

		CurNodeName=CurNode->name;

			//XMLCHAR STRING CONVERSION
			string *nodeValue = new string();
			char* CurNodeNameChar = (char*)CurNodeName;
			*nodeValue=CurNodeNameChar;
			stringValue=*nodeValue;

	} else {
		
		stringValue="ROOT-ELEMENT-NOT-DEFINED";
	}
return stringValue;
};

string XaLibDom::GetElementValueByXPath(xmlDocPtr XmlDomDoc,string XPathExpr) {

	xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj;
	xmlNodePtr cur;
	string stringValue="";

    xpathCtx = xmlXPathNewContext(XmlDomDoc);

    if(xpathCtx != NULL) {

    // Evaluate xpath expression
	    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);
	
	    if(xpathObj != NULL) {
	   	
			xmlNodeSetPtr nodes=xpathObj->nodesetval;
	
	    	int size = (nodes) ? nodes->nodeNr : 0;
	    	
			if (size!=0){
	
		        assert(nodes->nodeTab[0]);
		        
		        if(nodes->nodeTab[0]->type == XML_ELEMENT_NODE) {
		
					cur = nodes->nodeTab[0];
					
					if(cur->children!=NULL){
						xmlChar* CurNodeValue=cur->children->content;
		
						string *nodeValue = new string();
				
						char* CurNodeValueChar = (char*)CurNodeValue;
						*nodeValue=CurNodeValueChar;
						stringValue=*nodeValue;
		
					} else {
		
						stringValue="ELEMENT-NOT-DEFINED";
					}
		   		}
	
			} else {
				
				stringValue="ELEMENT-NOT-DEFINED";
			}
			
	   } else {
			
			stringValue="ERROR-XPATH-EXPRESSION";
	   }


	} else {
		
		stringValue="ERROR-XML-DOCUMENT";
	}

	xmlXPathFreeContext(xpathCtx);
	return stringValue;
};

string XaLibDom::GetNumRowByXPath(xmlDocPtr XmlDomDoc,string XPathExpr) {

	xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj;
	string stringValue="";
 
    xpathCtx = xmlXPathNewContext(XmlDomDoc);
	xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

	int RowNumber=xpathObj->nodesetval->nodeNr;
	
	ostringstream ss;
	ss << RowNumber;
 
return ss.str();
};

int XaLibDom::GetNumRowByXPathInt(xmlDocPtr XmlDomDoc,string XPathExpr) {

	xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj;
	string stringValue="";
 
    xpathCtx = xmlXPathNewContext(XmlDomDoc);
	xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

	int RowNumber=xpathObj->nodesetval->nodeNr;

return RowNumber;
};

void XaLibDom::UpdateElementValueByXPath(xmlDocPtr XmlDomDoc, VectorXPathExpr XPathExpr, VectorXPathValue XPathValue) {

	if (XmlDomDoc != NULL) {
    
		if(XPathExpr.size()==XPathValue.size()){

			for(unsigned n=0; n<XPathExpr.size(); ++n) {

				string xpath=XPathExpr.at(n);
				string value=XPathValue.at(n);

				UpdateValue(XmlDomDoc, (const xmlChar *)xpath.c_str(),(const xmlChar *)value.c_str());
			}

			xmlXPathFreeObject(xpathObj);
			xmlXPathFreeContext(xpathCtx);

		} else{

			cout<<"wrong number of value and expression";
		}
	
	} else {
	}
};

void XaLibDom::UpdateValue(xmlDocPtr XmlDomDoc, const xmlChar* xpathExpr, const xmlChar* value) {

    xpathCtx = xmlXPathNewContext(XmlDomDoc);
    if(xpathCtx == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        xmlFreeDoc(XmlDomDoc); 
    }

    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL) {
        fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(XmlDomDoc); 
    }

    UpdateXpathNodes(xpathObj->nodesetval, value);

};

void XaLibDom::UpdateXpathNodes(xmlNodeSetPtr nodes, const xmlChar* value) {
    int size;
    int i;
    
    assert(value);
    size = (nodes) ? nodes->nodeNr : 0;
 
    for(i = size - 1; i >= 0; i--) {
	assert(nodes->nodeTab[i]);
	
	xmlNodeSetContent(nodes->nodeTab[i], value);

	if (nodes->nodeTab[i]->type != XML_NAMESPACE_DECL)
	    nodes->nodeTab[i] = NULL;
    }
};

XaLibDom::ParamFromDomMap XaLibDom::MapParamFromDom(xmlDocPtr XmlDomDoc, VectorKey VectorKey,string SearchStartTag, string RecursiveTag){

	xmlDocPtr doc=XmlDomDoc;

	xmlNodePtr cur=NULL;
	xmlNodePtr cur_node = NULL;

	if (doc == NULL ) {
		
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Dom Object Is not defined");

	} else {

			cur = xmlDocGetRootElement(doc);
			int checkParamsTag=xmlStrcmp(cur->name, (const xmlChar*)SearchStartTag.c_str());

			if (checkParamsTag!=0) {

				LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Xml document does not contain or is not root child element -> " +SearchStartTag);

			} else {

				cur=cur->children;
				cur=cur->next;
				
				int i=0;
				for (cur_node = cur; cur_node; cur_node = cur_node->next) {

        			if (cur_node->type == XML_ELEMENT_NODE && xmlStrcmp(cur_node->name, (const xmlChar*) RecursiveTag.c_str())==0) {

						this->ParseParamFromDom(doc,cur_node,VectorKey,i);

						i++;
    				}
    			}
			}
	}

	xmlFreeDoc(doc);
	xmlCleanupParser();
	
	return ParamFromDom;

};

XaLibDom::ParamFromDomMap XaLibDom::MapParamFromDomByXPath(xmlDocPtr XmlDomDoc, VectorKey VectorKey, string XPathExpr, string SearchStartTag, string RecursiveTag){

	xmlDocPtr doc=XmlDomDoc;

	xmlXPathContextPtr xpathCtx=nullptr; 
    xmlXPathObjectPtr xpathObj;

	xmlNodePtr cur=NULL;
	xmlNodePtr cur_node = NULL;

	if (doc == NULL ) {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Dom Object Is not defined");

	} else {

		//cur = xmlDocGetRootElement(doc);

		xpathCtx = xmlXPathNewContext(XmlDomDoc);
		if(xpathCtx != NULL) {
			
			xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);
			
			if(xpathObj != NULL) {
			
				xmlNodeSetPtr nodes=xpathObj->nodesetval;
				int size = (nodes) ? nodes->nodeNr : 0;

				if (size!=0) {

					assert(nodes->nodeTab[0]);
		        
					if(nodes->nodeTab[0]->type == XML_ELEMENT_NODE) {
		
						cur = nodes->nodeTab[0];

						cur=cur->children;
						cur=cur->next;

						int checkParamsTag=xmlStrcmp(cur->name, (const xmlChar*)SearchStartTag.c_str());

						if (checkParamsTag!=0) {

							LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Xml document does not contain or is not root child element -> " +SearchStartTag);

						} else {

							cur=cur->children;
							cur=cur->next;

							int i=0;
							for (cur_node = cur; cur_node; cur_node = cur_node->next) {

								if (cur_node->type == XML_ELEMENT_NODE && xmlStrcmp(cur_node->name, (const xmlChar*) RecursiveTag.c_str())==0) {

									this->ParseParamFromDom(doc,cur_node,VectorKey,i);

									i++;
								}
							}
						}

					} else {

						LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Result Of XPath Query Is Not An XmlNode");

					}

				} else {

					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"XPath Expression Result Is Null -> "+XPathExpr);

				}

			} else {

				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Evaluating XPath Expression -> "+XPathExpr);

			}

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error To Create XPath Context");

		}
	}

	xmlFreeDoc(doc);
	xmlCleanupParser();
	xmlXPathFreeContext(xpathCtx);

	return ParamFromDom;
};

void XaLibDom::ParseParamFromDom (xmlDocPtr doc, xmlNodePtr cur, VectorKey VectorKey, int counter) {

	xmlChar *key;
	char* keyChar;

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {

		for(unsigned j=0; j<VectorKey.size(); ++j) {

			if (cur->type == XML_ELEMENT_NODE && (!xmlStrcmp(cur->name, (const xmlChar*)VectorKey.at(j).c_str()))) {
				
				string *nodeValue = new string();
				
				string StringKey=VectorKey.at(j).c_str();
				string StringValue="";

				key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
				keyChar = (char*)key;
				*nodeValue=keyChar;
				
				if (*nodeValue!="") {

					StringValue=*nodeValue;
				} else {
					
					StringValue="";
				}
				
				ParamFromDom[counter][StringKey]=StringValue;

				cur=cur->next;
				cur=cur->next;

			} else {

			}
		}

		cur=cur->next;
	}
	
};

string XaLibDom::HtmlFromStringAndFile(const vector<string>& HtmlFiles,const vector<string>& XmlStrings,const vector<string>& JsVarFiles,const vector<string>& JsVarStrings,int type) {

	string Html="<!DOCTYPE html><html id=\"html\">";
	ifstream MyFile;

	string HeadContent;
	string BodyContent;

	for ( auto i=0;i<HtmlFiles.size();i++) {

		MyFile.open(HtmlFiles[i].c_str());

		if (MyFile.is_open()) {

			string TmpString;
			string Content;

			while(getline(MyFile,TmpString)) {

				XaLibChar::ClearReturn(TmpString);
				Content.append(TmpString);
			}

			if (i==0) {
			//HEAD
				HeadContent.append(Content);

			} else {	
			//OTHER HTMLs
				BodyContent.append(Content);
			};
			
			TmpString={""};
			Content={""};

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Opening File -> "+HtmlFiles[i]);
		}

		MyFile.close();
	};

	string Js={};
	
	for (auto i=0;i<JsVarFiles.size();i=i+2) {

		MyFile.open(JsVarFiles[i+1].c_str());

		if (MyFile.is_open()) {

			string TmpString={};
			string Content="<script>"+JsVarFiles[i]+"=\"";


			while(getline(MyFile,TmpString)) {

				XaLibChar::ClearReturn(TmpString);
				XaLibChar::ClearSpaceXml(TmpString);
				XaLibChar::EscapeForJs(TmpString);

				Content.append(TmpString);
			}
			
			Content.append("\";</script>");

			Js.append(Content);

			TmpString={""};
			Content={""};

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Opening File -> "+JsVarFiles[i+1]);
		};

		MyFile.close();
	};

	for (auto i=0;i<JsVarStrings.size();i=i+2) {

		Js.append("<script>"+JsVarStrings[i]+"=\""+JsVarStrings[i+1]+"\";</script>");

	};

	Html.append("<head>"+HeadContent+Js+"</head>");
	Html.append("<body>"+BodyContent+"</body>");
	Html.append("</html>");	

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Generated HTML Page -> "+Html);
	
	
	return Html;	
};

void XaLibDom::AddAddressElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Id, string Type,string Value){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "address",NULL);	

	xmlNewChild(OptionsNode, NULL, (xmlChar *) "id", (const xmlChar *)Id.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "type", (const xmlChar *)Type.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "value", (const xmlChar *)Value.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlCleanupParser();
};

void XaLibDom::AddDeviceElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Id, string Active){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "device",NULL);	

	xmlNewChild(OptionsNode, NULL, (xmlChar *) "id", (const xmlChar *)Id.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "active", (const xmlChar *)Active.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlCleanupParser();
};

void XaLibDom::AddDateElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string Value){

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"date string -> " +Value);

	if (Value!="") {

		xmlNodePtr cur;
   		xmlNodePtr OptionsNode;

		xpathCtx = xmlXPathNewContext(XmlDomDoc);
	    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   		cur = xpathObj->nodesetval->nodeTab[0];

		OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "date",NULL);	

		xmlNewChild(OptionsNode, NULL, (xmlChar *) "year", (const xmlChar *)Value.substr(0,4).c_str());
		xmlNewChild(OptionsNode, NULL, (xmlChar *) "month", (const xmlChar *)Value.substr(5,2).c_str());
		xmlNewChild(OptionsNode, NULL, (xmlChar *) "day", (const xmlChar *)Value.substr(8,2).c_str());
	
		xmlXPathFreeObject(xpathObj);
	    xmlXPathFreeContext(xpathCtx);
	    xmlCleanupParser();

	} else {

	}
    
};

void XaLibDom::AddOptionElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string OptionLabel, string OptionValue){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "option",NULL);	

	
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "label", (const xmlChar *)OptionLabel.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "value", (const xmlChar *)OptionValue.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

void XaLibDom::AddOptionElementByXPath(xmlDocPtr XmlDomDoc, string& XPathExpr, vector<string>& OptionLabel, vector<string>& OptionValue){
	
	if (OptionLabel.size()!=OptionValue.size()) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error 31: Number Of Labels Is different From Number Of Values");
		throw 31;	
	};

	xmlNodePtr cur;

   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];
	
	
	for (auto i=0;i<OptionLabel.size();i++) {
	
		OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "option",NULL);

		xmlNewChild(OptionsNode, NULL, (xmlChar *) "label", (const xmlChar *)OptionLabel[i].c_str());
		xmlNewChild(OptionsNode, NULL, (xmlChar *) "value", (const xmlChar *)OptionValue[i].c_str());

	};
	
	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

void XaLibDom::AddValueElementByXPath(xmlDocPtr XmlDomDoc, string XPathExpr, string ValueValue){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "value", (const xmlChar *)ValueValue.c_str());	

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

void XaLibDom::AddOrgTreeOu(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName, string XaUserType_ID){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "ou",NULL);
	xmlNewProp (OptionsNode, (xmlChar *) "id", (const xmlChar *) OuId.c_str());

	xmlNewChild(OptionsNode, NULL, (xmlChar *) "id", (const xmlChar *)OuId.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "name", (const xmlChar *)OuName.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "user_type", (const xmlChar *)XaUserType_ID.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

void XaLibDom::AddOrgTreeUser(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "user",NULL);
	xmlNewProp (OptionsNode, (xmlChar *) "id", (const xmlChar *) OuId.c_str());

	xmlNewChild(OptionsNode, NULL, (xmlChar *) "id", (const xmlChar *)OuId.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "name", (const xmlChar *)OuName.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

void XaLibDom::AddOrgTreeUser(xmlDocPtr XmlDomDoc, string XPathExpr, string OuId, string OuName, string Department, string JobTitle){

	xmlNodePtr cur;
   	xmlNodePtr OptionsNode;

	xpathCtx = xmlXPathNewContext(XmlDomDoc);
    xpathObj = xmlXPathEvalExpression((const xmlChar *)XPathExpr.c_str(), xpathCtx);

   	cur = xpathObj->nodesetval->nodeTab[0];

	OptionsNode = xmlNewChild(cur, NULL, (const xmlChar *) "user",NULL);
	xmlNewProp (OptionsNode, (xmlChar *) "id", (const xmlChar *) OuId.c_str());

	xmlNewChild(OptionsNode, NULL, (xmlChar *) "id", (const xmlChar *)OuId.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "name", (const xmlChar *)OuName.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "department", (const xmlChar *)Department.c_str());
	xmlNewChild(OptionsNode, NULL, (xmlChar *) "jobtitle", (const xmlChar *)JobTitle.c_str());

	xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
};

XaLibDom::~XaLibDom() {
};