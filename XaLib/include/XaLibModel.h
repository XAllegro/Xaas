#ifndef XALIBMODEL_H
#define XALIBMODEL_H

#include <XaLibBase.h>
#include <XaLibChar.h>
#include <XaLibHttp.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibDom.h>
#include <XaLibSql.h>
#include <XaLibCrypto.h>

extern XaLibLog LOG;
extern XaLibHttp HTTP;
extern XaLibDb DB_SESSION;
extern XaLibDb DB_READ;
extern XaLibDb DB_WRITE;
extern XaLibDb DB_LOG;

extern XaSession SESSION;
extern XaRequest REQUEST;
extern XaResponse RESPONSE;
extern XaSettings SETTINGS;

class XaLibModel : protected XaLibBase {

    private:

    protected:

        //vector<string> XmlModels;

        //string DbTable;
        //vector <string> Fields;
        //vector <string> Values;

        //vector<string> ReturnedFields;
        //vector<string> WhereFields;
        //vector<string> WhereValues;
        //vector<string> OrderByFields;
        //vector<string> GroupByFields;

        //int Limit=0;

        //void ResetPoperites ();

        virtual void Dispatcher (const string &CalledEvent)=0;

        void DumpDbResMap(DbResMap& DbRes);
        
        vector<string> AddXmlFile(const vector<string>& FileName);

        void CreatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue);
        
        int CreateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue);

        string CreateResponse(const int& NextId);

        vector<string> ReadPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields=0);
        string ReadResponse(DbResMap& DbRes,vector<string>& FieldsToRead);

        vector<string> ListPrepare(const vector<string>& XmlFiles,const string& XPathExpr,const int& WithSystemFields=0);
        string ListResponse(DbResMap& DbRes,vector<string>& FieldsToRead);

        /*
	INSERT INTO table (col1, col2, col3, ...)
	SELECT col1, col2, col3, ... FROM table
	WHERE PrimaryKey = 1
        */
        int BackupRecord(const string& DbTable,const int& RowId);

		void UpdatePrepare(const vector<string>& XmlFiles,const string& XPathExpr,vector <string>& FieldName,vector <string>& FieldValue);
		int UpdateExecute(const string& DbTable,vector <string>& FieldName,vector <string>& FieldValue, const int& Id);
	
        string UpdateResponse(const int& UpdatedId);

        int DeleteExecute(const string& DbTable,const string& RowId);
        string DeleteResponse(const int& DeletedId);

        string BuildXml(DbResMap& ResMap,const string& Container,const string& GroupBy);

        //virtual void Create()=0;
        //virtual void Read()=0;
//        virtual void List()=0;
        //virtual void Delete()=0;
        //virtual void Update()=0;

    public:

        void Execute();

        XaLibModel ();
        virtual ~XaLibModel ();
};
#endif