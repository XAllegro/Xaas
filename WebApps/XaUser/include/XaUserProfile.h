#ifndef XAUSERPROFILE_H
#define XAUSERPROFILE_H

#include <XaLibAction.h>

using namespace std;

class XaUserProfile : public XaLibAction {

    private:

		void Dispatcher(const string& CalledEvent);

		void XaUserProfileXaUserActionAddFrm();
		void XaUserProfileXaUserActionAdd();
		void XaUserProfileGetXaUserActionAsOptions();

		void XaUserProfileAddFrm();
		void XaUserProfileAdd();
		void XaUserProfileMod();
		void XaUserProfileList();

	protected:

	public:

        XaUserProfile();
		~XaUserProfile();

		int EventIsFree (const string& CalledObject, const string& CalledEvent);
		int EventProfile (const string& CalledObject, const string& CalledEvent);

};
#endif
