#ifndef XAUSERADDRESSGEOTYPE_H
#define XAUSERADDRESSGEOTYPE_H

#include <XaLibModel.h>

class XaUserAddressGeoType : public XaLibModel {

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

        XaUserAddressGeoType();
        ~XaUserAddressGeoType();
};
#endif