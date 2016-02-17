#ifndef XAUSERLOGINUI_H
#define XAUSERLOGINUI_H

#include <XaLibAction.h>

class XaUserLoginUi : public XaLibAction {
	
    private:

		typedef vector<string> CondFields;
		typedef vector<string> CondValues;
		typedef vector<string> OrderByFields;

		typedef map<int, map<string,double> > TotalSalaryMap;
		typedef map<int, map<string,string> > TotalUserDataMap;
		typedef map<int, map<string,string> > TotalSalaryDataMap;

		void Dispatcher(const string &CalledEvent);

		void LoginFrm();
		void Login();
		void Logout();
                void LogoutFrm();

	protected:

	public:

		XaUserLoginUi();
		virtual ~XaUserLoginUi();
	
		//string GetTreeParentId(string XaUserId,string XaUserTypeId);
};
#endif
