#ifndef XALIBSQL_H
#define XALIBSQL_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibLog.h>

extern XaLibLog LOG;
extern XaSettings SETTINGS;

/**
 * @brief Abstraction layer for database interaction
 *
 * @details Database interaction:
 * this class implements Sql statements, the database connection is established from the controller. 
 *
 * @see XaLibDb
 * @see XaLibController
 * 
 * 
 * @see http://www.xallegro.com
 * @author Alessandro Mariotti
*/

class XaLibSql : protected XaLibBase {

    private:

    protected:

    public:

        XaLibSql();
        ~XaLibSql();

        /**
        * Adds new record to database.
        *
        * @param LibDb Active database connection
        * @param TableName Database Table Name
        * @param VectorFields vector<string> containing names of table fields
        * @param VectorValues vector<string> containing values of table fields
        * @return the inserted record ID
        *
        * Example Usage: INSERT INTO MyTable (name,description) VALUES ("Name", "Description");
        *
        * @code
        *
        * string Name=HTTP.GetHttpParam("Name");
        * string Description=HTTP.GetHttpParam("Description");
        * 
        * vector<string> VectorFields ={"name","description"}; 
        * vector<string> VectorValues ={Name,Description};
        *
        * int NextId=XaLibSql::Insert(DB_WRITE,"MyTable",VectorFields,VectorValues);
        * 
        * @endcode
        *
        */
        static int CheckRow(XaLibDb& LibDb,string TableName,string RowId,string Status,string Condition);
        
        static int Insert(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,const vector<string>& VectorValues);
        static int InsertMulti(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,vector<vector<string> > VectorValues);
        static int Update(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,const vector<string>& VectorValues,const vector<string>& WhereFields,const vector<string>& WhereValues);

        static int Delete(XaLibDb& LibDb,string TableName, const vector<string>& WhereFields,const vector<string>& WhereValues);
        static void DeleteOne(XaLibDb& LibDb,string TableName,string RowId);
        static int DeleteOneLogic(XaLibDb& LibDb,string TableName,string RowId);
        static int DeleteOneLogicWithKey(XaLibDb& LibDb,string TableName,string RowId,string KeyTable,string KeyId);

        static DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId);
        static DbResMap SelectOne(XaLibDb& LibDb,string TableName, int RowId,int Active, int Deleted);

        static DbResMap Select(XaLibDb& LibDb,const string& TableName,const vector<string>& ReturnedFields);
        static DbResMap Select(XaLibDb& LibDb,const string& TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues);
        static DbResMap Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields);
        //static DbResMap Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields, const vector<string>& GroupByFields);
        static DbResMap Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields,const vector<string>& GroupByFields,const int& Limit=0);

        static DbResMap FreeQuerySelect(XaLibDb& LibDb,string& SqlQry);
        static int FreeQueryInsert(XaLibDb& LibDb,string& SqlQry);

        static void FreeQueryNoRes(XaLibDb& LibDb,string SqlQry);

        //LOCKING AND TRANSACTION
        static void LockTable(XaLibDb& LibDb,string TableName);
        static void UnlockTable(XaLibDb& LibDb);

        static void TransactionStart(XaLibDb& LibDb);
        static void TransactionCommit(XaLibDb& LibDb);
        static void TransactionRollback(XaLibDb& LibDb);
        static vector<string> ColumnsList(XaLibDb& LibDb, const string& TableName);
};
#endif
