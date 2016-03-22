#include <XaDomain.h>
#include <XaLibModel.h>


XaDomain::XaDomain(){
};

void XaDomain::Dispatcher (const string &CalledEvent) {

    if (CalledEvent=="Create"){
        this->Create();
    } else if (CalledEvent=="Read"){
        this->Read();
    } else if (CalledEvent=="ReadForUpdateFrm"){
        this->ReadForUpdateFrm();
    } else if (CalledEvent=="List"){
	this->List();
    } else if (CalledEvent=="ListAsOptions"){
	this->ListAsOptions();
    } else if (CalledEvent=="Update"){
	this->Update();
    } else if (CalledEvent=="Delete"){
	this->Delete();
    } else if (CalledEvent=="AddAttributes"){
	this->AddAttributes();
    } else {
	LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"ERROR-42 Requested Event Does Not Exists -> "+CalledEvent);
	throw 42;
    }
};

void XaDomain::Create() {

        vector<string> FieldName;	
	vector<string> FieldValue;
	CreatePrepare({"XaDomain"},"/XaDomain/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=CreateResponse(CreateExecute("XaDomain",FieldName,FieldValue));
};

void XaDomain::Read() {

	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field");
	
	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",FieldsToRead,{"id"},{HTTP.GetHttpParam("id")});
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
};

void XaDomain::ReadForUpdateFrm() {

	string Id=HTTP.GetHttpParam("id");

	vector<string> ReadFields=ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field",0);

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReadFields},{"id"},{Id});

	RESPONSE.Content=ReadResponse(DbRes,ReadFields);
};

void XaDomain::List() {

	vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	string OrderBy=HTTP.GetHttpParam("order_by");
	string Status=HTTP.GetHttpParam("status");

	vector<string> ReturnedFields=ListPrepare({"XaDomain"},"/XaDomain/fieldset/field");

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);	
	//Quali campi
	//
	/*
	vector<string> FieldsToRead = XaLibModel::ReadPrepare({"XaDomain"},"/XaDomain/fieldset/field");
	DbResMap DbRes = ReadExecute("XaDomain",FieldsToRead,HTTP.GetHttpParam("id"));
	RESPONSE.Content= ReadResponse(DbRes,FieldsToRead);
	*/
};

void XaDomain::ListAsOptions() {
        string Domain=HTTP.GetHttpParam("domain");
	string TreeParentId=HTTP.GetHttpParam("tree_parent_ID");
        
        vector<string> WhereFields={};
	vector<string> WhereValues={};
	vector<string> OrderByFields={};
	vector<string> GroupByFields={};

	/*LIMIT*/
	string PassedLimit=HTTP.GetHttpParam("limit");
	int Limit={0};

	if (PassedLimit!="NoHttpParam") {
		Limit=FromStringToInt(PassedLimit);
	};

	/*ORDER BY*/
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
        
        if (Domain!="NoHttpParam") {

		WhereFields.push_back("domain");
		WhereValues.push_back(Domain);
	};
        
        if (TreeParentId!="NoHttpParam") {

		WhereFields.push_back("tree_parent_ID");
		WhereValues.push_back(TreeParentId);
	};

	vector<string> ReturnedFields={"id","name"};

	DbResMap DbRes=XaLibSql::Select(DB_READ,"XaDomain",{ReturnedFields},{WhereFields}, {WhereValues}, {OrderByFields},{GroupByFields},Limit);
	RESPONSE.Content=ListResponse(DbRes,ReturnedFields);
};

void XaDomain::Update() {
        
        int Id=FromStringToInt(HTTP.GetHttpParam("id"));
        vector<string> FieldName;	
	vector<string> FieldValue;
	UpdatePrepare({"XaDomain"},"/XaDomain/fieldset/field",FieldName,FieldValue);
	RESPONSE.Content=UpdateResponse(UpdateExecute("XaDomain",FieldName,FieldValue,Id));
};

void XaDomain::Delete() {

	int DeletedId=DeleteExecute("XaDomain",HTTP.GetHttpParam("id"));
	RESPONSE.Content=DeleteResponse(DeletedId);
};

void XaDomain::AddAttributes() {
    string All=HTTP.GetHttpParam("all");
    string Name=HTTP.GetHttpParam("name");
    
    string cond="";
    if (All=="yes")	{
        cond="";
    } else if (Name!="") {
        cond=" AND rp_att.name = '"+Name+"'";
    }
    
    string Qry="SELECT rp_att.id,check_type AS type,rp_att.name,disp AS label,rp_att.has_value FROM rp_att,rp_att_t,rp_label_it WHERE (rp_att.id < 600 OR rp_att.id >700) AND rp_att.is_active=1 AND rp_att.rp_att_t_id=rp_att_t.id AND rp_label_it.rp_att_id=rp_att.id AND check_type NOT IN ('system','external')"+cond+" ORDER BY rp_att.id";
            
    DbResMap DbRes=XaLibSql::FreeQuerySelect(DB_READ,Qry);
    
    unique_ptr<XaLibChar> LibChar (new XaLibChar());
    
    for (unsigned int i=0; i<DbRes.size();i++){
        
        string Domain=CreateDomainName(DbRes[i]["name"]);
        
        vector<string> FieldName;	
	vector<string> FieldValue;
        
        FieldName.push_back("domain");
	FieldValue.push_back(Domain);
        
        FieldName.push_back("name");
	FieldValue.push_back(DbRes[i]["name"]);
        
        FieldName.push_back("description");
	FieldValue.push_back(LibChar->UnclearAmpersand(DbRes[i]["label"]));
        
        FieldName.push_back("type");
	FieldValue.push_back(DbRes[i]["type"]);
        
        FieldName.push_back("tree_parent_ID");
	FieldValue.push_back("0");
        
        string NextId=FromIntToString(CreateExecute("XaDomain",FieldName,FieldValue));
        
        FieldName.clear();
        FieldValue.clear();
        
        Qry="SELECT val AS value,rp_att_v.name AS name,disp AS label FROM rp_att_v,rp_label_it WHERE rp_att_v.id=rp_label_it.rp_att_v_id AND rp_att_v.rp_att_id="+DbRes[i]["id"]+" ORDER BY val";
    
        DbResMap DbRes1=XaLibSql::FreeQuerySelect(DB_READ,Qry);
        
        for (unsigned int l=0; l<DbRes1.size();l++){
            
            FieldName.push_back("domain");
            FieldValue.push_back(Domain+"-Value");

            FieldName.push_back("name");
            FieldValue.push_back(DbRes1[l]["name"]);

            FieldName.push_back("description");
            FieldValue.push_back(LibChar->UnclearAmpersand(DbRes1[l]["label"]));

            FieldName.push_back("type");
            FieldValue.push_back(DbRes[i]["type"]+"-value");
            
            FieldName.push_back("tree_parent_ID");
            FieldValue.push_back(NextId);
            
            CreateExecute("XaDomain",FieldName,FieldValue);
        
            FieldName.clear();
            FieldValue.clear();
        }
    }
    
    RESPONSE.Content="Ok";
};

string XaDomain::CreateDomainName(string String) {

    char c=String[0];
    c=toupper(c);
    String.replace(0,1,FromCharToString(c));
    
    int pos;
    pos=0;
    pos=String.find("_");

    if (pos !=-1) {

        while (pos!=-1){
            char c=String[pos+1];
            c=toupper(c);
            String.replace(pos,2,FromCharToString(c));
            pos=String.find("_",pos+1);
        }

    }
    
    return "Rp"+String;
};

XaDomain::~XaDomain(){
};