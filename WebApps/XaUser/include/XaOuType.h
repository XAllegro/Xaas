#ifndef XAOUTYPE_H
#define XAOUTYPE_H

#include <XaLibModel.h>

class XaOuType : public XaLibModel {

    private:		

        //vector<string> PropsName;
        //vector<string> PropsValue;
        //vector<string> PropsType;
        
        void Create();
        void Read();
        void Update();
        void Delete();
        void List();
        void ListAsOptions();

    protected:

    public:

        void Dispatcher (const string &CalledEvent);

        XaOuType();
        ~XaOuType();
};
#endif