#ifndef XALIBDB_H
#define XALIBDB_H

#include <XaLibBase.h>
#include <mysql.h>

extern XaSettings SETTINGS;

class XaLibDb : private XaLibBase {

    private:

        MYSQL* ConnWrite;
        MYSQL* ConnRead;
        MYSQL* ConnSession;
        MYSQL* ConnLog;
        int ActiveConnection;

    protected:

    public:

        XaLibDb();
        ~XaLibDb();

        int Connect(const int& DbType);

        int ExInsert(string SqlQry);
        int ExUpdate(string SqlQry);
        int ExDelete(string SqlQry);
        DbResMap ExSelect(string SqlQry);
        DbResMap RetrieveRows(MYSQL_RES *DbResult);

        int ExSystemQry(string SqlQry);
        vector<string> FetchFields(const string& TableName);
		
        //DbResMap ExSelectSession(string SqlQry);
	//int ExInsertSession(string SqlQry);
};
#endif