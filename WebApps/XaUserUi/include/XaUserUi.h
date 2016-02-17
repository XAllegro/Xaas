#ifndef XAUSERUI_H
#define XAUSERUI_H

#include <XaLibAction.h>

class XaUserUi : public XaLibAction {
	
    private:

		//typedef vector<string> CondFields;
		//typedef vector<string> CondValues;
		//typedef vector<string> OrderByFields;

		//typedef map<int, map<string,double> > TotalSalaryMap;
		//typedef map<int, map<string,string> > TotalUserDataMap;
		//typedef map<int, map<string,string> > TotalSalaryDataMap;

		void Dispatcher(const string &CalledEvent);

		void LoginFrm();
		void Login();
		void Logout();
		void LogoutFrm();

		void List();

		//void XaUserLoginAddFrm();
		//void XaUserLoginAdd();
		//void XaUserLoginModFrm();
		//void XaUserLoginMod();
		//void XaUserLoginView();
		//void XaUserLoginList();
		//void XaUserLoginRowMod();

		//void XaUserPasswordModFrm();
		//void XaUserPasswordMod();

		//void XaUserCompanyAddFrm();
		//void XaUserCompanyList();
		//void XaUserCompanyView();
		//void XaUserCompanyModFrm();
		//void XaUserCompanyMod();

		//void XaUserDepartmentAddFrm();
		//void XaUserDepartmentView();
		//void XaUserDepartmentModFrm();
		//void XaUserDepartmentMod();

		//void XaUserOrgChart();
		//void XaUserOrgChartView();

		//void XaUserRegistrationFrm();
		//void XaUserRegistration();

		//void GetUsersAsOptions();
	
		//string CalculateTreeLevel(string ParentTreeLevel);
		//string CalculateTreePath(string ParentTreePath,int NextId);
		//void UpdateTreeData(DbResMap DbResParent,int NextId);
		
		//void XaUserXaDomainAddFrm();
		//void XaUserXaDomainAdd();
		//void AddOptionsAllSection(XaLibDom* LibDom,xmlDocPtr XmlDomDoc,string XPathExpr);
		//void XaUserGetXaDomainAsOptions();
		
		//void XaUserCheckIfExist();

	protected:

		//void GetTreeChildren(string TableName,int TreeStart,int TreeLevels,int WithStart);
		//void GetAllLeaves(string TableName);
		//void UpdateTreeData(int ParentId,int NextId);
		//void XaUserXaUserProfileAdd(int XaUser_ID,int XaUserProfile_ID);
		//void SetOldId(int NextId);

		// servono per import in XaUserEmployee
		//void XaUserCompanyAdd();
		//void XaUserDepartmentAdd();

		//DbResMap GetXaUserList(string XaUserType,string Field,string Value,string ResField,string OrderBy,string Condition, string Filter);

		//XaUser::DbResMap GetUsersByMonth(string StrUserCondition,string TreeParent_ID,string StrCurrentMonth, string StrCurrentYear, string StrDeliberationId, string ReportType);
		//string GetTreeParentType(string TreeParentID);
		//string ComposeXaUserBreadcrumb(string TreeParentID);
		//void GetMyChildren (string TableName,string XPathExpr,int TreeStart);
		//void XaUserGetAllCompanyDepartmentSection ();

	public:

		XaUserUi();
		//virtual int Authenticate(string StrEmail,string StrPassword);
		virtual ~XaUserUi();
	
		//string GetTreeParentId(string XaUserId,string XaUserTypeId);
};
#endif
