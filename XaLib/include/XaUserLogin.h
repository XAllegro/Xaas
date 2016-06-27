#ifndef XAUSERLOGIN_H
#define XAUSERLOGIN_H

#include <XaLibModel.h>
#include <XaLibToken.h>

class XaUserLogin : public XaLibModel {
	
    private:

        void Dispatcher(const string &CalledEvent);

        void Login();
        void Logout();
        void ReadByToken();
        void ChangePassword();
        void AddPhoto();
        void ReadPhoto();

    protected:

    public:

        XaUserLogin();
        virtual ~XaUserLogin();
};
#endif
