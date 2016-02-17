#include <XaLibSql.h>

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibChar.h>

XaLibSql::XaLibSql(){
};

int XaLibSql::Insert(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,const vector<string>& VectorValues){
		
	XaLibChar* LibChar=new XaLibChar();
	
	string SqlQry="INSERT INTO ";
	SqlQry.append(TableName);

	//ADDING FIELDS
	SqlQry.append("(");
	
		for(unsigned n=0; n<VectorFields.size(); ++n) {
	     
	     	if(n==VectorFields.size()-1){
	     		
	     		SqlQry.append(VectorFields.at(n));

	     	} else{
	     		SqlQry.append(VectorFields.at(n));
	     		SqlQry.append(",");
	     	}
	    }

	//ADDING VALUES
	SqlQry.append(") VALUES (");

		for(unsigned n=0; n<VectorValues.size(); ++n) {

	     	if(n==VectorValues.size()-1){
	     		SqlQry.append("\"");
	     		SqlQry.append(VectorValues.at(n));
	     		SqlQry.append("\"");

	     	} else {

	     		SqlQry.append("\"");
	     		string ToAppend=LibChar->ClearSqlEntities(VectorValues.at(n));

	     		SqlQry.append(ToAppend);

	     		SqlQry.append("\"");
	     		SqlQry.append(",");
	     	}
	    }
	SqlQry.append(")");
	
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Query Insert -> " +SqlQry);

	unsigned NextId=LibDb.ExInsert(SqlQry);

	delete LibChar;

	if (NextId==0) {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Executing Query Insert -> " +SqlQry);
		return 0;

	} else {

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Query Insert -> " +SqlQry);
		return NextId;
	}

};


int XaLibSql::InsertMulti(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,vector<vector<string> > VectorValuesMulti){
	
	XaLibChar* LibChar=new XaLibChar();
	
	string SqlQry="INSERT INTO ";
	SqlQry.append(TableName);

	//ADDING FIELDS
	SqlQry.append("(");
	
	for(unsigned n=0; n<VectorFields.size(); ++n) {
	     
		if(n==VectorFields.size()-1){
	     		
			SqlQry.append(VectorFields.at(n));

		} else{
	    	SqlQry.append(VectorFields.at(n));
	     	SqlQry.append(",");
		}
	}

	SqlQry.append(") VALUES ");
	//ADDING VALUES

	for(unsigned i=0; i<VectorValuesMulti.size(); ++i) {

		vector<string> VectorValues=VectorValuesMulti.at(i);

   		SqlQry.append("(");

		for(unsigned n=0; n<VectorValues.size(); ++n) {

	     	if(n==VectorValues.size()-1){
	     		SqlQry.append("\"");
	     		SqlQry.append(VectorValues.at(n));
	     		SqlQry.append("\"");

	     	} else{
	     		SqlQry.append("\"");
	     		string ToAppend=LibChar->ClearSqlEntities(VectorValues.at(n));

	     		SqlQry.append(ToAppend);

	     		SqlQry.append("\"");
	     		SqlQry.append(",");
	     	}
		}

     	SqlQry.append(")");

		if (i != VectorValuesMulti.size()-1) {
			SqlQry.append(",");
		}

	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Query Insert -> " +SqlQry);
	
	unsigned NextId=LibDb.ExInsert(SqlQry);	// e' l'id del primo record inserito

	delete LibChar;

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Query Insert -> " +SqlQry);

	if (NextId==0){

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error occurred inserting a new Record in -> "+ TableName);

		return 0;

	} else {

		return NextId;

	}
};


int XaLibSql::Update(XaLibDb& LibDb,string TableName,const vector<string>& VectorFields,const vector<string>& VectorValues, const vector<string>& WhereFields,const vector<string>& WhereValues) {

	if (WhereFields.size()>0 && WhereFields.size()==WhereValues.size()){

		XaLibChar* LibChar=new XaLibChar();

		string SqlQry="UPDATE ";

		SqlQry.append(TableName);
		SqlQry.append(" SET ");

		for(unsigned n=0; n<VectorFields.size(); ++n) {

     		SqlQry.append(VectorFields.at(n));
     		SqlQry.append("=\"");
   
     		SqlQry.append(LibChar->ClearSqlEntities(VectorValues.at(n)));
     		SqlQry.append("\"");

	     	if(n==VectorFields.size()-1){

	     	} else {

	     		SqlQry.append(",");
	     	}
	    }

		SqlQry.append(" WHERE 1=1");

		for(unsigned m=0; m<WhereFields.size(); ++m) {

			SqlQry.append(" AND ");
			SqlQry.append(WhereFields.at(m));
			SqlQry.append("=\"");
			SqlQry.append(LibChar->ClearSqlEntities(WhereValues.at(m)));
			SqlQry.append("\"");

		}

		delete (LibChar);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Query Update  -> " +SqlQry);

		unsigned Updated=LibDb.ExUpdate(SqlQry);

		if (Updated==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error occurred updating Record in -> "+ TableName);

			return 0;

		} else {

			return Updated;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Executing Query Update Without WHERE");

		return 0;
	}
};

int XaLibSql::Delete(XaLibDb& LibDb,string TableName, const vector<string>& WhereFields,const vector<string>& WhereValues) {

	if (WhereFields.size()>0 && WhereFields.size()==WhereValues.size()){

		XaLibChar* LibChar=new XaLibChar();

		string SqlQry="DELETE FROM ";

		SqlQry.append(TableName);

		SqlQry.append(" WHERE 1=1");

		for(unsigned m=0; m<WhereFields.size(); ++m) {

			SqlQry.append(" AND ");
			SqlQry.append(WhereFields.at(m));
			SqlQry.append("=\"");
			SqlQry.append(LibChar->ClearSqlEntities(WhereValues.at(m)));
			SqlQry.append("\"");

		}

		delete (LibChar);

		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Query DELETE  -> " +SqlQry);

		unsigned Status=LibDb.ExDelete(SqlQry);

		if (Status==0){

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error occurred Delete Record in -> "+ TableName);

			return 0;

		} else {

			return Status;
		}

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Executing Query Delete Without WHERE");
		
		return 0;
	}
};

void XaLibSql::DeleteOne(XaLibDb& LibDb,string TableName,string RowId){

	string SqlQry="DELETE FROM ";
	SqlQry.append(TableName);
	SqlQry.append(" WHERE id=\"");
	SqlQry.append(RowId);
	SqlQry.append("\"");

	//cout<<SqlQry<<endl;
	LibDb.ExUpdate(SqlQry);

};

int XaLibSql::DeleteOneLogic(XaLibDb& LibDb,string TableName,string RowId){

	string SqlQry="UPDATE ";
	SqlQry.append(TableName);
	SqlQry.append(" SET active=0, deleted=1 WHERE id=\"");
	SqlQry.append(RowId);
	SqlQry.append("\"");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Query DeleteLogic  -> " +SqlQry);

	unsigned DeleteId=LibDb.ExUpdate(SqlQry);

	if (DeleteId==0){

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error occurred logically deleting Record in -> "+ TableName);

		return 0;

	} else {

		return DeleteId;
	}

};

int XaLibSql::DeleteOneLogicWithKey(XaLibDb& LibDb,string TableName,string RowId,string KeyTable,string KeyId){

	string SqlQry="UPDATE ";
	SqlQry.append(TableName);
	SqlQry.append(" SET active=\"0\", deleted=\"1\" WHERE id=\"");
	SqlQry.append(RowId);
	SqlQry.append("\" AND XaTable=\"");
	SqlQry.append(KeyTable);
	SqlQry.append("\" AND XaField_ID=\"");
	SqlQry.append(KeyId);
	SqlQry.append("\" ");

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing Query DeleteLogicWithKey -> " +SqlQry);


	unsigned DeleteId=LibDb.ExUpdate(SqlQry);

	if (DeleteId==0){

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error occurred logically deleting Record in -> "+ TableName);

		return 0;

	} else {

		return DeleteId;
	}

};

XaLibBase::DbResMap XaLibSql::SelectOne(XaLibDb& LibDb,string TableName, int RowId){

	DbResMap DbRes;

	string SqlQry="SELECT * FROM ";
	SqlQry.append(TableName);
	SqlQry.append(" WHERE ID=");
	SqlQry.append(to_string(RowId));

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);

	DbRes=LibDb.ExSelect(SqlQry);

	return DbRes;
};

XaLibBase::DbResMap XaLibSql::SelectOne(XaLibDb& LibDb,string TableName, int RowId, int Active, int Deleted){

	DbResMap DbRes;

	string SqlQry="SELECT * FROM ";
	SqlQry.append(TableName);
	SqlQry.append(" WHERE ID=");
	SqlQry.append(to_string(RowId));

	SqlQry.append(" AND active=");
	SqlQry.append(to_string(Active));
	SqlQry.append(" AND deleted=");
	SqlQry.append(to_string(Deleted));

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);
	DbRes=LibDb.ExSelect(SqlQry);
	

	return DbRes;
};

XaLibBase::DbResMap XaLibSql::Select(XaLibDb& LibDb,const string& TableName,const vector<string>& ReturnedFields) {

	DbResMap DbRes;
	
	string SqlQry="SELECT ";

	unique_ptr<XaLibChar> LibChar (new XaLibChar());

		if(ReturnedFields.at(0)=="*"){
			
			SqlQry.append("*");
			
		} else {
			
			for(unsigned m=0; m<ReturnedFields.size(); ++m) {
			
				SqlQry.append(ReturnedFields.at(m));

				if(m==ReturnedFields.size()-1){

	     	} else {

				SqlQry.append(",");
	     	}
	    }
	}

	SqlQry.append(" FROM ");
	SqlQry.append(TableName);
	
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);

	DbRes=LibDb.ExSelect(SqlQry);

	return DbRes;

}

XaLibBase::DbResMap XaLibSql::Select(XaLibDb& LibDb,const string& TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues) {

	DbResMap DbRes;
	
	string SqlQry="SELECT ";

		XaLibChar* LibChar=new XaLibChar();

		if(ReturnedFields.at(0)=="*"){
			
			SqlQry.append("*");
			
		} else {
			
			for(unsigned m=0; m<ReturnedFields.size(); ++m) {
			
				SqlQry.append(ReturnedFields.at(m));

				if(m==ReturnedFields.size()-1){

	     	} else {

				SqlQry.append(",");
	     	}
	    }
	}

	SqlQry.append(" FROM ");
	SqlQry.append(TableName);


	if (WhereFields.size()==WhereValues.size() && WhereFields.size()>0 ){
	
		SqlQry.append(" WHERE ");

		for(unsigned n=0; n<WhereFields.size(); ++n) {

     		SqlQry.append(WhereFields.at(n));
     		SqlQry.append("=\"");
     		string ToAppend=LibChar->ClearSqlEntities(WhereValues.at(n));
     		SqlQry.append(ToAppend);
     		SqlQry.append("\"");

	     	if(n==WhereFields.size()-1){

	     	} else{

	     		SqlQry.append(" AND ");
	     	}
	    }

	} else {
		//NUMERO VALORI E CAMPI DIVERSO
	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);
		
	DbRes=LibDb.ExSelect(SqlQry);

	delete LibChar;
	return DbRes;
};

XaLibBase::DbResMap XaLibSql::Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields) {
	
	DbResMap DbRes;
	
	string SqlQry="SELECT ";

		XaLibChar* LibChar=new XaLibChar();

		if(ReturnedFields.at(0)=="*"){
			
			SqlQry.append("*");
			
		} else {
			
			for(unsigned m=0; m<ReturnedFields.size(); ++m) {
			
				SqlQry.append(ReturnedFields.at(m));

				if(m==ReturnedFields.size()-1){

	     	} else {

				SqlQry.append(",");
	     	}
	    }
	}

	SqlQry.append(" FROM ");
	SqlQry.append(TableName);


	if (WhereFields.size()==WhereValues.size() && WhereFields.size()>0 ){

		SqlQry.append(" WHERE ");

		for(unsigned n=0; n<WhereFields.size(); ++n) {

     		SqlQry.append(WhereFields.at(n));
     		SqlQry.append("=\"");
     		string ToAppend=LibChar->ClearSqlEntities(WhereValues.at(n));
     		SqlQry.append(ToAppend);
     		SqlQry.append("\"");

	     	if(n==WhereFields.size()-1){

	     	} else{

	     		SqlQry.append(" AND ");
	     	}
	    }

	} else {
		//NUMERO VALORI E CAMPI DIVERSO
	}

	if (OrderByFields.size()>0 ){

		SqlQry.append(" ORDER BY ");

		for(unsigned n=0; n<OrderByFields.size(); ++n) {

     		SqlQry.append(OrderByFields.at(n));

	     	if(n==OrderByFields.size()-1){

	     	} else{

	     		SqlQry.append(",");
	     	}
	    }

	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);
	
	DbRes=LibDb.ExSelect(SqlQry);

	delete LibChar;
	return DbRes;

}

/*
XaLibBase::DbResMap XaLibSql::Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields,const vector<string>& GroupByFields) {

	DbResMap DbRes;
	
	string SqlQry="SELECT ";

		XaLibChar* LibChar=new XaLibChar();

		if(ReturnedFields.at(0)=="*"){
			
			SqlQry.append("*");
			
		} else {
			
			for(unsigned m=0; m<ReturnedFields.size(); ++m) {
			
				SqlQry.append(ReturnedFields.at(m));

				if(m==ReturnedFields.size()-1){

	     	} else {

				SqlQry.append(",");
	     	}
	    }
	}

	SqlQry.append(" FROM ");
	SqlQry.append(TableName);


	if (WhereFields.size()==WhereValues.size() && WhereFields.size()>0 ){

		SqlQry.append(" WHERE ");

		for(unsigned n=0; n<WhereFields.size(); ++n) {

     		SqlQry.append(WhereFields.at(n));
     		SqlQry.append("=\"");
     		string ToAppend=LibChar->ClearSqlEntities(WhereValues.at(n));
     		SqlQry.append(ToAppend);
     		SqlQry.append("\"");

	     	if(n==WhereFields.size()-1){

	     	} else{

	     		SqlQry.append(" AND ");
	     	}
	    }

	} else {
		//NUMERO VALORI E CAMPI DIVERSO
	}

	if (OrderByFields.size()>0 ){

		SqlQry.append(" ORDER BY ");

		for(unsigned n=0; n<OrderByFields.size(); ++n) {

     		SqlQry.append(OrderByFields.at(n));

	     	if(n==OrderByFields.size()-1){

	     	} else{

	     		SqlQry.append(",");
	     	}
	    }

	}
	
	if (GroupByFields.size()>0 ){

		SqlQry.append(" GROUP BY ");

		for(unsigned n=0; n<GroupByFields.size(); ++n) {

     		SqlQry.append(GroupByFields.at(n));

	     	if(n==GroupByFields.size()-1){

	     	} else{

	     		SqlQry.append(",");
	     	}
	    }

	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);

	DbRes=LibDb.ExSelect(SqlQry);

	delete LibChar;
	return DbRes;

}
*/
XaLibBase::DbResMap XaLibSql::Select(XaLibDb& LibDb,string TableName,const vector<string>& ReturnedFields,const vector<string>& WhereFields, const vector<string>& WhereValues, const vector<string>& OrderByFields,const vector<string>& GroupByFields,const int& Limit) {

	DbResMap DbRes;
	
	string SqlQry="SELECT ";

		XaLibChar* LibChar=new XaLibChar();

		if(ReturnedFields.at(0)=="*"){
			
			SqlQry.append("*");
			
		} else {
			
			for(unsigned m=0; m<ReturnedFields.size(); ++m) {
			
				SqlQry.append(ReturnedFields.at(m));

				if(m==ReturnedFields.size()-1){

	     	} else {

				SqlQry.append(",");
	     	}
	    }
	}

	SqlQry.append(" FROM ");
	SqlQry.append(TableName);


	if (WhereFields.size()==WhereValues.size() && WhereFields.size()>0 ){

		SqlQry.append(" WHERE ");

		for(unsigned n=0; n<WhereFields.size(); ++n) {

     		SqlQry.append(WhereFields.at(n));
     		SqlQry.append("=\"");
     		string ToAppend=LibChar->ClearSqlEntities(WhereValues.at(n));
     		SqlQry.append(ToAppend);
     		SqlQry.append("\"");

	     	if(n==WhereFields.size()-1){

	     	} else{

	     		SqlQry.append(" AND ");
	     	}
	    }

	} else {
		//NUMERO VALORI E CAMPI DIVERSO
	}

	if (OrderByFields.size()>0 ){

		SqlQry.append(" ORDER BY ");

		for(unsigned n=0; n<OrderByFields.size(); ++n) {

     		SqlQry.append(OrderByFields.at(n));

	     	if(n==OrderByFields.size()-1){

	     	} else{

	     		SqlQry.append(",");
	     	}
	    }

	}
	
	if (GroupByFields.size()>0 ){

		SqlQry.append(" GROUP BY ");

		for(unsigned n=0; n<GroupByFields.size(); ++n) {

     		SqlQry.append(GroupByFields.at(n));

	     	if(n==GroupByFields.size()-1){

	     	} else{

	     		SqlQry.append(",");
	     	}
	    }

	}

	if (Limit!=0) {
	
		SqlQry.append(" LIMIT ");
		SqlQry.append(to_string(Limit));
	}

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executing  Select -> " +SqlQry);

	DbRes=LibDb.ExSelect(SqlQry);

	delete LibChar;
	return DbRes;

}

int XaLibSql::CheckRow(XaLibDb& LibDb,string TableName,string RowId,string Status,string Condition) {
	
        string SqlQry="SELECT id FROM "+TableName+" WHERE id="+RowId+" AND status="+Status+" "+Condition;
	DbResMap DbRes=LibDb.ExSelect(SqlQry);
	
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Check Row -> " +SqlQry);
	
	return DbRes.size();
};

XaLibBase::DbResMap XaLibSql::FreeQuerySelect(XaLibDb& LibDb,string& SqlQry){
	
	DbResMap DbRes;
	DbRes=LibDb.ExSelect(SqlQry);

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Free Query -> " +SqlQry);
	
	return DbRes;
};

int XaLibSql::FreeQueryInsert(XaLibDb& LibDb,string& SqlQry) {
	
	unsigned NextId=LibDb.ExInsert(SqlQry);	
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Free Query Insert-> " +SqlQry);

	return NextId;
};

void XaLibSql::FreeQueryNoRes(XaLibDb& LibDb,string SqlQry){

	LibDb.ExUpdate(SqlQry);
	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Executed Query Free No Result -> " +SqlQry);

};

void XaLibSql::LockTable(XaLibDb& LibDb,string TableName){

	string SqlQry="LOCK TABLES "+ TableName + " WRITE";
	int i=LibDb.ExSystemQry(SqlQry);
	
	if (i==1) {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Locked Database Table -> " + TableName);
	
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Locking Database Table -> " + TableName);

	}
};

void XaLibSql::UnlockTable(XaLibDb& LibDb){

    string SqlQry="UNLOCK TABLES";
	int i=LibDb.ExSystemQry(SqlQry);

	if (i==1) {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"UnLocked Database Tables");
	
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error UnLocking Database Tables");

	}
};

void XaLibSql::TransactionStart(XaLibDb& LibDb){

	string SqlQry="START TRANSACTION";
	int i=LibDb.ExSystemQry(SqlQry);

	
	if (i==1) {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Start Transaction");
	
	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Starting Transaction");
	}
};

void XaLibSql::TransactionCommit(XaLibDb& LibDb){

	string SqlQry="COMMIT";
	int i=LibDb.ExSystemQry(SqlQry);

	
	if (i==1) {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Commit Transaction");

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Committing Transaction");
	}
};

void XaLibSql::TransactionRollback(XaLibDb& LibDb){

	string SqlQry="ROLLBACK";
	int i=LibDb.ExSystemQry(SqlQry);
	
	if (i==1) {
	
		LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Rollback Transaction");

	} else {

		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Error Rollback Transaction");
	}

};

vector<string> XaLibSql::ColumnsList (XaLibDb& LibDb, const string& TableName) {

			LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"XXXXXXXX 1 -> ");

	return LibDb.FetchFields(TableName);
};

XaLibSql::~XaLibSql(){
};
