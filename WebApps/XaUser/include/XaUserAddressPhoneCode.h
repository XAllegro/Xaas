#ifndef XAUSERADDRESSPHONECODE_H
#define XAUSERADDRESSPHONECODE_H

#include <XaLibModel.h>

class XaUserAddressPhoneCode : public XaLibModel {

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

        XaUserAddressPhoneCode();
        ~XaUserAddressPhoneCode();
};
#endif