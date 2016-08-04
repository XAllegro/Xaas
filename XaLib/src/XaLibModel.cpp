#include <XaLibModel.h>

XaLibModel::XaLibModel() {
};

vector<string> XaLibModel::AddXmlFile(const vector<string>& FileName){

	vector<string> XmlFiles;

	for (auto &i : FileName) {

		//BUILDING THE PATH
		string XmlDefaultPath=SETTINGS["XmlDir"]+i+".xml";
		string XmlSharedPath=SETTINGS["SharedDir"]+"xml/"+i+".xml";

		//TEST THE FILE
		unique_ptr<FILE, int(*)(FILE*)> f1(fopen(XmlDefaultPath.c_str(), "r"), fclose);
		unique_ptr<FILE, int(*)(FILE*)> f2(fopen(XmlSharedPath.c_str(), "r"), fclose);

		//ADD THE FILE TO THE VECTOR
		if (f1) {
			XmlFiles.push_back(XmlDefaultPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Custom-> "+XmlDefaultPath);

		} else if (f2) {
			XmlFiles.push_back(XmlSharedPath);
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Added XmlFile Shared-> "+XmlSharedPath);

		} else {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Requested Xml File Does Not Exist -> "+i);
			throw 203;
		}
	}

	return XmlFiles;
};

void XaLibModel::CreatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue){

	vector <string> Properties ={"name","db_type","size","create","required"};

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FCreate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/create");
		
        if (FCreate=="yes") {

			// add field only if creatable

			string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
			string FType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

            string FValue=HTTP.GetHttpParam(FName);

			if (FValue!="NoHttpParam") {
				// add field only if not empty
				// check field value
				if (FType=="select-single-domain") {
					string Domain=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/options/domain");
					CheckDomain(FValue,Domain);
				}
				FieldName.push_back(FName);
				FieldValue.push_back(FValue);
			} else {
				// empty field is skipped from add
				if (FRequired=="yes") {
					// error if field is empty and required
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-205 Required Parameter is Missing -> "+FName);
					throw 205;
				}
			}

        }
		
	};
};

void XaLibModel::CreatePrepare(const vector<string>& XmlFiles,const vector<string>& XmlStrings,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue){

	vector <string> Properties ={"name","db_type","size","create","required"};

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(AddXmlFile(XmlFiles),XmlStrings,0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FCreate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/create");
		
        if (FCreate=="yes") {

			// add field only if creatable

			string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
			string FType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

            string FValue=HTTP.GetHttpParam(FName);

			if (FValue!="NoHttpParam") {
				// add field only if not empty
				// check field value
				if (FType=="select-single-domain") {
					string Domain=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/options/domain");
					CheckDomain(FValue,Domain);
				}
				FieldName.push_back(FName);
				FieldValue.push_back(FValue);
			} else {
				// empty field is skipped from add
				if (FRequired=="yes") {
					// error if field is empty and required
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-205 Required Parameter is Missing -> "+FName);
					throw 205;
				}
			}

        }
		
	};
};

int XaLibModel::CreateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue) {

	FieldName.push_back("status");
	FieldName.push_back("updated_by");
	FieldValue.push_back("1");
	FieldValue.push_back(FromIntToString(SESSION.XaUser_ID));
	
	
	//CHECK FIELDS
	//vector <string> Fields={"status","old_id"};
	//vector <string> Values={"1","0"};
/*
	for (auto i=0;i<LoadedFields.size();i++) {

		Fields.push_back(LoadedFields[i]["name"]);	
		Values.push_back(LoadedFields[i]["value"]);
	};
*/
	int NextId=XaLibSql::Insert(DB_WRITE,DbTable,FieldName,FieldValue);

	if (NextId==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-301 Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));
		throw 301;
	}

	int UpdatedOrig=XaLibSql::Update(DB_WRITE,DbTable,{"orig_id"},{FromIntToString(NextId)},{"id"},{FromIntToString(NextId)});

	if (UpdatedOrig==0) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-3011 Failed to initialize orig_id for a new record into table -> "+DbTable+" with id ->"+to_string(NextId));
		throw 3011;
	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Inserted a new record into table -> "+DbTable+" with id ->"+to_string(NextId));

	return NextId;
};

string XaLibModel::CreateResponse(const int& NextId) {

	return "<create>"+to_string(NextId)+"</create>";
};

vector<string> XaLibModel::ReadPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields) {

	//TODO:GESTIONE ERRORI
	vector<string> FieldsToRead;

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);
	
	for (auto i=0;i<FieldsNum;i++) {

		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/read")=="yes"){
		
			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};

	};
	
	auto it = FieldsToRead.begin();
	it = FieldsToRead.insert ( it , "id" );

	if (WithSystemFields==1) {
		FieldsToRead.push_back("updated_by");
		FieldsToRead.push_back("updated");
		FieldsToRead.push_back("status");
		FieldsToRead.push_back("orig_id");
	}

	//SE E" VUOTO
	return FieldsToRead;
};

string XaLibModel::ReadResponse(DbResMap& DbRes,vector<string>& FieldsToRead) {

	string Res="<read>";
	
	for (auto &i: FieldsToRead) {
			
		Res.append("<"+i+">");
		Res.append(DbRes[0][i]);
		Res.append("</"+i+">");
	};

	Res.append("</read>");
	return Res;	
};

vector<string> XaLibModel::ReadForUpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields) {

	//TODO:GESTIONE ERRORI
	vector<string> FieldsToRead;

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);
	
	for (auto i=0;i<FieldsNum;i++) {

		if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update")=="yes"){
		
			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		};

	};
	
	auto it = FieldsToRead.begin();
	it = FieldsToRead.insert ( it , "id" );

	if (WithSystemFields==1) {
		FieldsToRead.push_back("updated_by");
		FieldsToRead.push_back("updated");
		FieldsToRead.push_back("status");
		FieldsToRead.push_back("orig_id");
	}

	//SE E" VUOTO
	return FieldsToRead;
};

vector<string> XaLibModel::ListPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields) {

	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FIELDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	vector<string> FieldsToRead;

	for (auto i=0;i<FieldsNum;i++) {

		//if (XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/list")=="yes") {

			FieldsToRead.push_back(XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name"));
		//};

	};

	
	auto it = FieldsToRead.begin();
	it = FieldsToRead.insert ( it , "id" );

	if (WithSystemFields==1) {
		FieldsToRead.push_back("updated_by");
		FieldsToRead.push_back("updated");
		FieldsToRead.push_back("status");
		FieldsToRead.push_back("orig_id");
	}

	return FieldsToRead;
};

string XaLibModel::ListResponse(DbResMap& DbRes,vector<string>& FieldsToRead) {

	string Res="<list>";

	for (auto j=0;j<DbRes.size();j++) {
	
		Res.append("<item>");

		for (auto &i: FieldsToRead) {

			Res.append("<"+i+">");
			
			if (DbRes[j][i]=="") {
				Res.append("null");

			} else {

				Res.append(DbRes[j][i]);
			}

			//Res.append(DbRes[j][i]);
			Res.append("</"+i+">");

		};

		Res.append("</item>");
	};

	Res.append("</list>");
	return Res;	
};

int XaLibModel::BackupRecord(const string& DbTable,const int& FieldId) {

	vector<string> Columns=XaLibSql::ColumnsList(DB_READ,DbTable);
	
	/* all other columns, included "updated", must be preserved */
	vector<string> ExcludeToList={"id","status","orig_id"};

	string List={};

	for(int i=0;i<Columns.size();i++) {

		auto it = find (ExcludeToList.begin(), ExcludeToList.end(), Columns[i]);

		if (it != ExcludeToList.end()) {

			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field Found In The Exclusion List -> "+Columns[i]);

		} else {

			List.append(Columns[i]+",");
			LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Field List Appending -> "+Columns[i]);
		}
	};

	//REMOVE LAST ","
	//string SqlCopiedColumns=List.substr(0, List.size()-1);
	//keep last comma since it is used to append SqlUpdatedColumns,SqlUpdatedValues later on
	string SqlCopiedColumns=List;

	string SqlUpdatedColumns="status,orig_id";
	string SqlUpdatedValues="'3','"+FromIntToString(FieldId)+"'";

	string SqlQry="INSERT INTO " + DbTable+" (" +SqlCopiedColumns + SqlUpdatedColumns +") SELECT "+SqlCopiedColumns + SqlUpdatedValues +" FROM "+DbTable+" WHERE id="+FromIntToString(FieldId); 

	LOG.Write("XXXXXXXXXXX", __FILE__, __FUNCTION__,__LINE__,SqlQry);
	
	
	unsigned NextId=XaLibSql::FreeQueryInsert(DB_WRITE,SqlQry);

	/* NO UPDATES allowed on the record just inserted, since they would alter the "updated" column, which must keep its previous value */

};

void XaLibModel::UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue){

	vector <string> Properties ={"name","db_type","size","create","required"};
	
	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FUpdate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update");

		if (FUpdate=="yes") {
			string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
			string FType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

			string FValue=HTTP.GetHttpParam(FName);

			if (FValue!="NoHttpParam") {
				// update field only if not empty
				// check field value
				if (FType=="select-single-domain") {
					string Domain=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/options/domain");
					CheckDomain(FValue,Domain);
				}
				FieldName.push_back(FName);
				FieldValue.push_back(FValue);
			} else {
				// empty field is skipped from update
				if (FRequired=="yes") {
					// error if field is empty and required
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-3022 Required field not found in Update -> "+FName);
					throw 3022;
				}
			}

		}
		
	};
}

/* Includes fields whose value must be set to Null */
void XaLibModel::UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue,vector <string>& FieldNullName){

	vector <string> Properties ={"name","db_type","size","create","required"};
	
	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromFile(AddXmlFile(XmlFiles),0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FUpdate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update");

		if (FUpdate=="yes") {

			// add field only if updatable

			string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");
			string FType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

            string FValue=HTTP.GetHttpParam(FName);

			if (FValue!="NoHttpParam") {
				// update field only if not empty
				// check field value
				if (FType=="select-single-domain") {
					string Domain=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/options/domain");
					CheckDomain(FValue,Domain);
				}
				FieldName.push_back(FName);
				FieldValue.push_back(FValue);
			} else {
				// empty field is skipped from update
				if (FRequired=="yes") {
					// error if field is empty and required
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-3022 Required field not found in Update -> "+FName);
					throw 3022;
				} else {
					// set to null
					FieldNullName.push_back(FName);
				}
			}

        }
	}
};

/* Includes fields whose value must be set to Null */
/* Xml model can be input as filename or string */
void XaLibModel::UpdatePrepare(const vector<string>& XmlFiles,const vector<string>& XmlStrings,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue,vector <string>& FieldNullName){

	vector <string> Properties ={"name","db_type","size","create","required"};
	
	//LOAD XML FOR MODEL
	xmlDocPtr XmlDomDoc=XaLibDom::DomFromStringAndFile(AddXmlFile(XmlFiles),XmlStrings,0);

	//GET NUMBER OF FILEDS
	int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

	/*For Each Field Check Properties and Load Value*/
	for (auto i=0;i<FieldsNum;i++) {

		string FUpdate=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/update");
		string FName=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/name");

		if (FUpdate=="yes") {

			// add field only if updatable

			string FType=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/type");
			string FSize=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/size");
			string FRequired=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/required");

            string FValue=HTTP.GetHttpParam(FName);

			if (FValue!="NoHttpParam") {
				// update field only if not empty
				// check field value
				if (FType=="select-single-domain") {
					string Domain=XaLibDom::GetElementValueByXPath(XmlDomDoc,XPathExpr+"["+ to_string(i+1) + "]/options/domain");
					CheckDomain(FValue,Domain);
				}
				FieldName.push_back(FName);
				FieldValue.push_back(FValue);
			} else {
				// empty field is skipped from update
				if (FRequired=="yes") {
					// error if field is empty and required
					LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-3022 Required field not found in Update -> "+FName);
					throw 3022;
				} else {
					// set to null
					FieldNullName.push_back(FName);
				}
			}

        } else if (FUpdate=="clear") {

			// clear field value to correct front-end tampering

			FieldNullName.push_back(FName);
		}
	}
};

int XaLibModel::UpdateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue, const int& Id) {

	FieldName.push_back("updated_by");
	FieldValue.push_back(FromIntToString(SESSION.XaUser_ID));

	BackupRecord(DbTable,Id);

	int Updated=XaLibSql::Update(DB_WRITE,DbTable,{FieldName},{FieldValue},{"id"},{XaLibBase::FromIntToString(Id)});

	if (Updated==1) {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated a record into table -> "+DbTable+" with id ->"+to_string(Id));
		return Id;
	} else {
		return 0;
	}

};

/* Includes fields whose value must be set to Null */
int XaLibModel::UpdateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue,vector <string>& FieldNullName, const int& Id) {

	FieldName.push_back("updated_by");
	FieldValue.push_back(FromIntToString(SESSION.XaUser_ID));

	BackupRecord(DbTable,Id);

	int Updated=XaLibSql::Update(DB_WRITE,DbTable,{FieldName},{FieldValue},{FieldNullName},{"id"},{XaLibBase::FromIntToString(Id)});

	if (Updated==1) {
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Updated a record into table -> "+DbTable+" with id ->"+to_string(Id));
		return Id;
	} else {
		return 0;
	}

};

string XaLibModel::UpdateResponse(const int& UpdatedId) {

	return "<update><id>"+to_string(UpdatedId)+"</id></update>";
};

int XaLibModel::DeleteExecute(const string& DbTable,const string& FieldId) {

	//TODO: ERROR CHECK
	if (XaLibSql::Update(DB_WRITE,DbTable,{"status"},{"4"},{"id"},{FieldId})==1){
	
		return FromStringToInt(FieldId);

	} else {

		return 0;
	}

};

string XaLibModel::DeleteResponse(const int& DeletedId) {

	return "<delete>"+to_string(DeletedId)+"</delete>";
};

void XaLibModel::Execute(){

	//EXECUTE OBJECT DISPATCHER (CLASS DISPATCHER)
	if (REQUEST.CalledObject!="" && REQUEST.CalledEvent!="") {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Object Event ->"+REQUEST.CalledEvent);
		this->Dispatcher(REQUEST.CalledEvent);

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Event Is empty");
		throw 41;
	}

};

void XaLibModel::GetXmlModel() {

	string ModelType=HTTP.GetHttpParam("type");
	string Id=HTTP.GetHttpParam("id");

	string ModelName=REQUEST.CalledObject;

	vector<string> XmlFiles=AddXmlFile({ModelName});

	string Content;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Model Type -> "+ModelType);

	if (ModelType=="CreateWithExternalKey") {

		unique_ptr<XaLibDom> LibDom(new XaLibDom());

		xmlDocPtr XmlDomDoc=LibDom->DomFromFile(XmlFiles,0);

		string XPathExpr="/"+ModelName+"/fieldset/field";
		int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

		for (auto i=0;i<FieldsNum;i++) {

			string NodePath=XPathExpr+"["+ to_string(i+1) +"]";
			string FType=LibDom->GetElementValueByXPath(XmlDomDoc,NodePath+"/type");

			if(FType=="external-key") {
				string FName=LibDom->GetElementValueByXPath(XmlDomDoc,NodePath+"/name");
				string FValue=HTTP.GetHttpParam(FName);
				LibDom->AddValueElementByXPath(XmlDomDoc,NodePath,FValue);
			}
		}

		Content=LibDom->StringFromDom(XmlDomDoc);

	} else if (ModelType=="Update") {
		/* Load Xml file and add <value> tag to nodes */

		/* model */
		unique_ptr<XaLibDom> LibDom(new XaLibDom());
		xmlDocPtr XmlDomDoc=LibDom->DomFromFile(XmlFiles,0);

		string XPathExpr="/"+ModelName+"/fieldset/field";
		int FieldsNum=XaLibDom::GetNumRowByXPathInt(XmlDomDoc,XPathExpr);

		/* data */
		vector<string> ReadFields=ReadForUpdatePrepare({ModelName},"/"+ModelName+"/fieldset/field",0);
		DbResMap DbRes=XaLibSql::Select(DB_READ,ModelName,{ReadFields},{"id"},{Id});
		xmlDocPtr XmlDomDocData=LibDom->DomFromString(ReadResponse(DbRes,ReadFields));

		for (auto i=0;i<FieldsNum;i++) {

			string NodePath=XPathExpr+"["+ to_string(i+1) +"]";
			string FType=LibDom->GetElementValueByXPath(XmlDomDoc,NodePath+"/type");

			string FName =LibDom->GetElementValueByXPath(XmlDomDoc,NodePath+"/name");
			string FValue=LibDom->GetElementValueByXPath(XmlDomDocData,"/read/"+FName);
			if (FValue=="ELEMENT-NOT-DEFINED") { FValue=""; };
			LibDom->AddValueElementByXPath(XmlDomDoc,NodePath,FValue);

		}

		Content=LibDom->StringFromDom(XmlDomDoc);

  } else {
	/* Retrieve Xml file the fastest way */
  
	ifstream MyFile;

	for (auto i=0;i<XmlFiles.size();i++) {

		MyFile.open(XmlFiles[i].c_str());

		if (MyFile.is_open()) {

			string TmpString;

			while(getline(MyFile,TmpString)) {
				XaLibChar::ClearReturn(TmpString);
				Content.append(TmpString);
			}
		}
	}
  }
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"XmlModel -> "+Content);

	RESPONSE.Content=Content;
};

/*
void XaLibModel::CheckHttpField(string FieldValue,string ControlType) {
	
	if (ControlType=="required"){
		
		if (FieldValue=="NoHttpParam" || FieldValue=="") {
			
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-205 Required Parameter is Missing");
			throw 205;
		}

	}

};
*/
void XaLibModel::CheckHttpField(vector<string> FieldValue,string ControlType) {

	if (ControlType=="required"){
		
		for (string& i : FieldValue ) {
		
			if (i=="NoHttpParam" || i=="") {
			
				LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-205 Required Parameter is Missing -> "+i);
				throw 205;
			}
		}

	}
};

void XaLibModel::CheckHttpFieldInDomain(string FieldValue,vector<string> DomainValues) {

	if(std::find(DomainValues.begin(), DomainValues.end(), FieldValue) != DomainValues.end()) {
		
		//DomainValues contain
		
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-207 The Value Is Out of Domain -> "+FieldValue);
		throw 207;
	}
	
};

bool XaLibModel::CheckDomain(string Id, string Domain) {
	
		bool check=false;

		DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{"id"},{"id","domain","status"},{Id,Domain,"1"});

		if (DbRes.size()==1) {
			check=true;
		}

		if (check) {
			return check;
		} else {
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-207 The Value Is Out of Domain -> "+Id+","+Domain);
			throw 207;
		}

}

bool XaLibModel::CheckDomainParent(string ChildId, string ParentId) {
	
		bool check=false;

		DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{"tree_parent_ID"},{"id","status"},{ChildId,"1"});

		if (DbRes.size()==1) {
			if (DbRes[0]["tree_parent_ID"]==ParentId) {
				check=true;
			}
		}

		if (check) {
			return check;
		} else {
			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-208 Wrong Parent in Domain -> "+ChildId+","+ParentId);
			throw 208;
		}

}

XaLibModel::~XaLibModel(){
};