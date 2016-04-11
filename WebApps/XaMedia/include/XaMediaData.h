#ifndef XAMEDIADATA_H
#define XAMEDIADATA_H

#include <XaLibModel.h>

class XaMediaData : public XaLibModel {

    private:
        
        void Dispatcher(const string &CalledEvent);
        
        void List();
	void Read();
        void Create();
        void Delete();
        
        string ComposeFileName(string XaMediaId);
        string ClearDate(string StringToClear);

    protected:

    public:

        XaMediaData();
	~XaMediaData();
};
#endif