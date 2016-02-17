#ifndef XAUSERADDRESSGEO_H
#define XAUSERADDRESSGEO_H

#include <XaLibModel.h>

class XaUserAddressGeo : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void Update();
        void Delete();
        void List();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaUserAddressGeo();
        ~XaUserAddressGeo();
};
#endif