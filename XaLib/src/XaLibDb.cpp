#include <XaLibDb.h>
#include <XaLibBase.h>
#include "XaLibChar.h"

/**
* Instannce of XaLibDb
* @param ParamsConfiguration - ParamsConfigurationMap - System Configuration
* @param LibLog - XaLibLog* - log Library
* @param MyLogFile - ofstream* - log stream file
* @param DbType - int - 1:=write 2:=read 3:=session 4:log
* @see
* @return void
*/

XaLibDb::XaLibDb(){
};

int XaLibDb::Connect(const int& DbType) {

	int XaStatus=0;
	
	vector<string> DbTypeName = {"","Write","Read","Session","Log"};

	this->ActiveConnection=DbType;

	const char* DbHost=SETTINGS["Db"+DbTypeName[DbType]+"Host"].c_str();
	const char* DbDatabase=SETTINGS["Db"+DbTypeName[DbType]+"Database"].c_str();
	const char* DbUser=SETTINGS["Db"+DbTypeName[DbType]+"User"].c_str();
	const char* DbPassword=SETTINGS["Db"+DbTypeName[DbType]+"Password"].c_str();
	unsigned int DbPort=atoi(SETTINGS["Db"+DbTypeName[DbType]+"Port"].c_str());
	
    if (DbType==1) {

        ConnWrite = mysql_init(NULL);

        if (mysql_real_connect(ConnWrite, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){

			XaLibBase::SendHtmlHeaders();
            printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));
			cout<< "Database Session Connection Problem->"+SETTINGS["DbWriteDatabase"]+" at->" + SETTINGS["DbWriteHost"]<<endl;
			
        } else {

			XaStatus=1;
        }
        
    } else if (DbType==2) {

        ConnRead = mysql_init(NULL);

        if (mysql_real_connect(ConnRead, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){
			
			XaLibBase::SendHtmlHeaders();
            printf("Error %u: %s\n", mysql_errno(ConnRead), mysql_error(ConnRead));	
			cout<< "Database Session Connection Problem->"+SETTINGS["DbReadDatabase"]+" at->" + SETTINGS["DbReadHost"]<<endl;
			
        } else {

			XaStatus=1;
        }

    } else if (DbType==3) {

        ConnSession = mysql_init(NULL);

        if (mysql_real_connect(ConnSession, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL){

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			cout<< "Database Session Connection Problem->"+SETTINGS["DbSessionDatabase"]+" at->" + SETTINGS["DbSessionHost"]<<endl;

        } else {

			XaStatus=1;
		}

	} else if (DbType==4) {

        ConnLog = mysql_init(NULL);

        if (mysql_real_connect(ConnLog, DbHost, DbUser, DbPassword, DbDatabase, DbPort, NULL, 0)==NULL) {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));	
			cout<< "Database Log Connection Problem->"+SETTINGS["DbLogDatabase"]+" at->" + SETTINGS["DbLogHost"]<<endl;

        } else {

			XaStatus=1;
		}

	} else {

    }
	
	return XaStatus;
};

int XaLibDb::ExInsert(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();

	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");
		
		if(mysql_query(ConnWrite, cstr)==0) {

			return mysql_insert_id(ConnWrite);

		} else {
			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));	
			return 0;

		}

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");

		if(mysql_query(ConnSession, cstr)==0) {

			return mysql_insert_id(ConnSession);

		} else {
			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			return 0;

		}

	} else if(this->ActiveConnection==4){

		
		mysql_query(ConnLog,"set character_set_server='utf8'");
		mysql_query(ConnLog,"SET NAMES 'utf8'");
				
		if(mysql_query(ConnLog, cstr)==0) {

			return mysql_insert_id(ConnLog);

		} else {
			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));	
			return 0;

		}

	} else {
		XaLibBase::SendHtmlHeaders();
		cout<< "Database Inserts Are Only Allowed For DB_WRITE - DB_SESSION - DB_LOG"<<endl;

		return 0;
	}

};

int XaLibDb::ExUpdate(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();
		
	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");

		if(mysql_query(ConnWrite, cstr)==0) {

			return 1;

		} else {
			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));	
			return 0;

		}

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		
		if(mysql_query(ConnSession, cstr)==0) {

			return 1;

		} else {
			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			return 0;

		}

	} else {

		XaLibBase::SendHtmlHeaders();
		cout<< "Database Updates Are Only Allowed For DB_WRITE - DB_SESSION"<<endl;
		return 0;
	}

};

int XaLibDb::ExDelete(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();
		
	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");

		if(mysql_query(ConnWrite, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));	
			return 0;
		}

	} else if(this->ActiveConnection==3){

		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");

		if(mysql_query(ConnSession, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			return 0;
		}

	} else if(this->ActiveConnection==4){

		mysql_query(ConnLog,"set character_set_server='utf8'");
		mysql_query(ConnLog,"SET NAMES 'utf8'");

		if(mysql_query(ConnLog, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));	
			return 0;
		}

	} else {

		XaLibBase::SendHtmlHeaders();
		cout<< "Database Deletes Are Only Allowed For DB_WRITE - DB_SESSION - DB_LOG "<<endl;
		return 0;
	}

};

XaLibDb::DbResMap XaLibDb::ExSelect(string SqlQry) {

	DbResMap DbRes;
	MYSQL_RES *result;

	string qry=SqlQry;
	const char *cstr = qry.c_str();

		if (this->ActiveConnection==2){

			mysql_query(ConnRead,"set character_set_server='utf8'");
			mysql_query(ConnRead,"SET NAMES 'utf8'");

			if (mysql_query(ConnRead, cstr)!=0){

				string log=qry.c_str();

				XaLibBase::SendHtmlHeaders();
				printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));
				cout<< "Error occurred during execution Query-> " + log<<endl;

				DbRes.clear();
				throw 28;
				return DbRes;

			} else {
			
				result = mysql_store_result(ConnRead);
				DbRes=this->RetrieveRows(result);
				return DbRes;
			}

		} else if(this->ActiveConnection==3){

			mysql_query(ConnSession,"set character_set_server='utf8'");
			mysql_query(ConnSession,"SET NAMES 'utf8'");

			if (mysql_query(ConnSession, cstr)!=0){

				string log=qry.c_str();


				XaLibBase::SendHtmlHeaders();
				printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));
				cout<< "Error occurred during execution Query-> " + log<<endl;

				DbRes.clear();
				throw 28;
				return DbRes;

			} else {

				result = mysql_store_result(ConnSession);
				DbRes=this->RetrieveRows(result);
				return DbRes;
			}

		} else if(this->ActiveConnection==4){

			mysql_query(ConnLog,"set character_set_server='utf8'");
			mysql_query(ConnLog,"SET NAMES 'utf8'");

			if (mysql_query(ConnLog, cstr)!=0){

				string log=qry.c_str();


				XaLibBase::SendHtmlHeaders();
				printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));
				cout<< "Error occurred during execution Query-> " + log<<endl;

				DbRes.clear();
				throw 28;
				return DbRes;

			} else {

				result = mysql_store_result(ConnLog);
				DbRes=this->RetrieveRows(result);
				return DbRes;
			}

		} else {
		
			DbRes.clear();
			return DbRes;
		}
};

XaLibDb::DbResMap XaLibDb::RetrieveRows(MYSQL_RES *DbResult) {

	DbResMap DbRes;

	MYSQL_RES *result=DbResult;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	vector<string> DbResultFieldName;

		unsigned int i = 0;

		while((field = mysql_fetch_field(result))) {

			DbResultFieldName.push_back(field->name);
		}

		//int numrows = mysql_num_rows(result);
		int numfields = mysql_num_fields(result);

		XaLibChar* LibChar=new XaLibChar();
		int j=0;
		while((row = mysql_fetch_row(result))) {

			for(i = 0; i < numfields; i++){

				string val="";

				if (row[i]==NULL){
					val = "";
				} else {
					val = LibChar->ClearXmlEntitiesBasic(row[i]);
					//val = row[i];
				}

				DbRes[j][DbResultFieldName.at(i)]=val;

			}
			j++;
		}

	return DbRes;
};

int XaLibDb::ExSystemQry(string SqlQry) {

	string qry=SqlQry;
	const char *cstr = qry.c_str();

	if (this->ActiveConnection==1){

		mysql_query(ConnWrite,"set character_set_server='utf8'");
		mysql_query(ConnWrite,"SET NAMES 'utf8'");

		if(mysql_query(ConnWrite, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnWrite), mysql_error(ConnWrite));	
			return 0;
		}

	} else if(this->ActiveConnection==2){

		mysql_query(ConnRead,"set character_set_server='utf8'");
		mysql_query(ConnRead,"SET NAMES 'utf8'");
		
		if(mysql_query(ConnRead, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));	
			return 0;
		}

	} else if(this->ActiveConnection==3){
	
		mysql_query(ConnSession,"set character_set_server='utf8'");
		mysql_query(ConnSession,"SET NAMES 'utf8'");
		
		if(mysql_query(ConnSession, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnSession), mysql_error(ConnSession));	
			return 0;
		}

	} else if(this->ActiveConnection==4){
	
		mysql_query(ConnLog,"set character_set_server='utf8'");
		mysql_query(ConnLog,"SET NAMES 'utf8'");
		
		if(mysql_query(ConnLog, cstr)==0) {

			return 1;

		} else {

			XaLibBase::SendHtmlHeaders();
			printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));
			return 0;
		}
	}

	return 1;

};

vector<string> XaLibDb::FetchFields(const string& TableName) {

	vector<string> FieldsList;	
	const char *cstr = TableName.c_str();

	MYSQL_RES *tbl_cols=nullptr;
	int i;
	
	if (this->ActiveConnection==1){
	
		tbl_cols = mysql_list_fields(ConnWrite, cstr, NULL);

	} else if(this->ActiveConnection==2){
	
		tbl_cols = mysql_list_fields(ConnRead, cstr, NULL);
	
	} else if(this->ActiveConnection==3){
			
		tbl_cols = mysql_list_fields(ConnSession, cstr, NULL);

	} else if(this->ActiveConnection==4){

		tbl_cols = mysql_list_fields(ConnLog, cstr, NULL);
			
	} else {

		XaLibBase::SendHtmlHeaders();
		printf("Error %u: %s\n", mysql_errno(ConnLog), mysql_error(ConnLog));
		//THROwARE
	}

	unsigned int field_cnt = mysql_num_fields(tbl_cols);

	for (i=0; i < field_cnt; ++i) {

		MYSQL_FIELD *col = mysql_fetch_field_direct(tbl_cols, i);
		FieldsList.push_back(col->name);
	};

	mysql_free_result(tbl_cols);

	return FieldsList;
};

XaLibDb::~XaLibDb() {
};