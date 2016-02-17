#ifndef XAUSERROLE_H
#define XAUSERROLE_H

#include <XaLibAction.h>

class XaUserRole : public XaLibAction {

    private:
		
		void Dispatcher(const string &CalledEvent);
		
		void XaUserRoleAddFrm();
		void XaUserRoleAdd();
		void XaUserRoleMod();
		void XaUserRoleList();

	protected:

	public:

		XaUserRole();		
		~XaUserRole();

};
#endif
