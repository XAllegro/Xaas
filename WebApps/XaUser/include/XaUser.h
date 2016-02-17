#ifndef XAUSER_H
#define XAUSER_H

#include <XaLibModel.h>
#include <XaLibToken.h>

class XaUser : public XaLibModel {
	
    private:

        void Dispatcher(const string &CalledEvent);

        void Login();
        void Logout();

        void Create();
        void Read();
        void Update();
        void Delete();

		void List();

    protected:

    public:

        XaUser();
        virtual ~XaUser();
};
#endif
