#ifndef XAUSERADDRESSMAIL_H
#define XAUSERADDRESSMAIL_H

#include <XaLibModel.h>

class XaUserAddressMail : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void ReadForUpdateFrm();
        void Update();
        void Delete();
        void List();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaUserAddressMail();
        ~XaUserAddressMail();
};
#endif