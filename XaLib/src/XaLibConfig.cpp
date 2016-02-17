#include <XaLibConfig.h>
#include <XaLibBase.h>

XaLibConfig::XaLibConfig(){
};

void XaLibConfig::GetParams(string& ConfFile){

	xmlDocPtr doc=NULL;
	xmlNodePtr cur=NULL;
	xmlNodePtr cur_node = NULL;

	string strDocFile;
	strDocFile.append(ConfFile);

	const char *docname = (char*)strDocFile.c_str();

	doc = xmlReadFile(docname,NULL,0);

	if (doc == NULL ) {
		SendHtmlHeaders();
		cout<<"the config file [config/config.xml] does not exist"<<endl;

	} else {

			cur = xmlDocGetRootElement(doc);
			int checkParamsTag=xmlStrcmp(cur->name, (const xmlChar*) "params");

			if (checkParamsTag!=0) {
			
				SendHtmlHeaders();
				cout<<"the config file does not contain the [params] element"<<endl;

			} else {

				cur=cur->children;
				cur=cur->next;
				
				for (cur_node = cur; cur_node; cur_node = cur_node->next) {

        			if (cur_node->type == XML_ELEMENT_NODE && xmlStrcmp(cur_node->name, (const xmlChar*) "param")==0) {

						this->ParseParam(doc,cur_node);

    				}
    			}
			}				
	}	

	xmlFreeDoc(doc);
	xmlCleanupParser();
};

void XaLibConfig::ParseParam (xmlDocPtr doc, xmlNodePtr cur) {

	char* valueChar;
	char* keyChar;
	xmlChar *key;
	xmlChar *value;

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {

		string *nodeValue = new string();
		string *nodeKey = new string();

 		if (cur->type == XML_ELEMENT_NODE && (!xmlStrcmp(cur->name, (const xmlChar*)"key"))) {
			
			key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			keyChar = (char*)key;
			*nodeKey=keyChar;

			cur=cur->next;
			cur=cur->next;
 		}

		if (cur->type == XML_ELEMENT_NODE && (!xmlStrcmp(cur->name, (const xmlChar*)"value"))) {

			value = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
			valueChar = (char*)value;
			*nodeValue=valueChar;

			cur=cur->next;
 		}

		if (*nodeKey!="" && *nodeValue!=""){

			string stringKey=*nodeKey;
			string stringValue=*nodeValue;

			SETTINGS.insert(pair<string, string>(stringKey,stringValue));
		}

		cur = cur->next;

		delete nodeValue;
 	    delete nodeKey;
	}
	
};

XaLibConfig::~XaLibConfig(){
};