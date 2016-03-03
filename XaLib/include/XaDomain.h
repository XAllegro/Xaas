#ifndef XADOMAIN_H
#define XADOMAIN_H

#include <XaLibModel.h>

class XaDomain : public XaLibModel {

    private:
        
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

        XaDomain();
        ~XaDomain();
};
#endif