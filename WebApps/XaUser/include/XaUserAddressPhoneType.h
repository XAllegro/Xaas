#ifndef XAUSERADDRESSPHONETYPE_H
#define XAUSERADDRESSPHONETYPE_H

#include <XaLibModel.h>

class XaUserAddressPhoneType : public XaLibModel {

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
        void ListAsOptions();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaUserAddressPhoneType();
        ~XaUserAddressPhoneType();
};
#endif