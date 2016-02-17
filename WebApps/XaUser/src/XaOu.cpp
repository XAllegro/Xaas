#include <XaOu.h>
#include <XaLibModel.h>

XaOu::XaOu(){
};


void XaOu::Dispatcher (const string &CalledEvent) {

	if (CalledEvent=="Create"){
		this->Create();
  //  } else if (CalledEvent=="List"){
	//	 this->List();
    } else if (CalledEvent=="ListAsOptions"){
		 this->ListAsOptions();
    } else if (CalledEvent=="Tree"){
		 this->Tree();
    } else if (CalledEvent=="Read"){
		 this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm"){
		 this->ReadForUpdateFrm();
    } else if (CalledEvent=="Update"){
		 this->Update();
    //} else if (CalledEvent=="Delete"){
		 //this->Delete();
    } else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42:: Requested Event Does Not Exists -> "+CalledEvent);
		throw 42;
	}
};

void XaOu::Create() {

	vector<string> FieldName;	
	vector<string> FieldValue;

	CreatePrepare({"XaOu"},"/XaOu/fieldset/field",FieldName,FieldValue);

	/*Get parent level*/
	int pos=PositionInVector(FieldName,"tree_parent_ID");

	if (pos==-1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-206:: Searched Element is Not present in the Vector");
		throw 206;
	};

	string tree_parent_ID= FieldValue[pos];

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Retrieved tree_parent_ID ->"+ tree_parent_ID);

	DbResMap Parent=XaLibSql::Select(DB_READ,"XaOu",{"id","tree_level","tree_path"},{"id"},{tree_parent_ID});

	if (Parent.size()!=1) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-304:: The record is not unique");
		throw 304;
	};

	/*CALCULATING TREE LEVEL*/
	string TreeLevel=FromIntToString((FromStringToInt(Parent[0]["tree_level"])+1));

	FieldName.push_back("tree_level");
	FieldValue.push_back(TreeLevel);

	int NextId=CreateExecute("XaOu",FieldName,FieldValue);

	/*CALCULATING TREE PATH*/
	string TreePath=Parent[0]["tree_path"]+FromIntToString(NextId)+"|";

	XaLibSql::Update(DB_WRITE,"XaOu",{"tree_path"},{TreePath},{"id"},{FromIntToString(NextId)});
	RESPONSE.Content=CreateResponse(NextId);
};


/*

XaOuModel::Delete(){
};

XaOuModel::XaOuModel(){
};
*/

void XaOu::ListAsOptions() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/* only option with id=passed value */
	string CurrentValue=HTTP.GetHttpParam("value");
	if (CurrentValue!="NoHttpParam") {
		WhereFields.push_back("id");
		WhereValues.push_back(CurrentValue);
	}
	
	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
	OrderByFields.push_back("tree_path");
	string PassedOrderBy=HTTP.GetHttpParam("order_by");
	
	if (PassedOrderBy!="NoHttpParam") {
		OrderByFields.push_back(PassedOrderBy);
	};
	
	/*STATUS*/
	string PassedStatus=HTTP.GetHttpParam("status");
	
	if (PassedStatus!="NoHttpParam") {

		WhereFields.push_back("status");
		WhereValues.push_back(PassedStatus);
	};

	//vector<string> ReturnedFields=ListPrepare({"XaOuType"},"/XaOuType/fieldset/field");

	vector<string> ReturnedFields={"id","name","tree_level"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOu",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaOu::Tree() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};
	vector<string> ReturnedFields={"id","name","tree_level","tree_parent_ID"};

	/*GET LEVEL*/
	string TreeLevel=HTTP.GetHttpParam("tree_level");
	WhereFields.push_back("tree_level");

	if (TreeLevel!="NoHttpParam") {

		WhereValues.push_back(TreeLevel);

	} else {

		/*DEFAULT CASE FIRST LEVEL*/
		WhereValues.push_back("1");
	};

	/*GET PARENT*/
	string ParentId=HTTP.GetHttpParam("tree_parent_ID");
	WhereFields.push_back("tree_parent_ID");

	if (ParentId!="NoHttpParam") {

		WhereValues.push_back(ParentId);

	} else {

		/*DEFAULT CASE PARENT 0*/
		WhereValues.push_back("0");
	};

	/*GET TYPE*/
	string XaOuTypeID=HTTP.GetHttpParam("XaOuType_ID");
	
	if (XaOuTypeID!="NoHttpParam") {

		WhereFields.push_back("XaOuType_ID");
		WhereValues.push_back(XaOuTypeID);
	};

	/*GET ORDER BY*/
	string OrderBy=HTTP.GetHttpParam("order_by");
	
	if (OrderBy!="NoHttpParam") {
		
		OrderByFields.push_back(OrderBy);
		
	} else {

		OrderByFields.push_back("name");
	};
	
	/*GET ORDER BY*/
	string Status=HTTP.GetHttpParam("status");
	WhereFields.push_back("status");
	
	if (Status!="NoHttpParam") {
		
		WhereValues.push_back(Status);
	} else {

		WhereValues.push_back("1");
	};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOu",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields});
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaOu::Read() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaOu"},"/XaOu/fieldset/field",0);

	string Qry="SELECT X1.id, X1.name, X1.description, XaOuType.name AS XaOuType_ID, X2.name AS tree_parent_ID FROM XaOu X1";
	Qry+=" LEFT JOIN XaOuType ON X1.XaOuType_ID=XaOuType.id";
	Qry+=" LEFT JOIN XaOu X2 ON X1.tree_parent_ID=X2.id";
	Qry+=" WHERE X1.id="+Id;
	
	DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaOu::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaOu"},"/XaOu/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaOu",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaOu::Update() {

	string Id=HTTP.GetHttpParam("id");
	int UpdateId=XaLibBase::FromStringToInt(Id);

	vector<string> FieldName;	
	vector<string> FieldValue;

	UpdatePrepare({"XaOu"},"/XaOu/fieldset/field",FieldName,FieldValue);

	int Updated=UpdateExecute("XaOu",FieldName,FieldValue,UpdateId);	
	
	/* Parent Id and tree are not updatable yet */
	/* Tree updates will have to be propagated to all descendants */
	
	RESPONSE.Content=UpdateResponse(Updated);

};

XaOu::~XaOu(){
};