#ifndef XAMEDIA_H
#define XAMEDIA_H

#include <XaLibModel.h>

class XaMedia : public XaLibModel {

    private:
        
        void Dispatcher(const string &CalledEvent);
        
        void List();
	void Read();
        void View();
        void Create();
        void Delete();
        void CreateComplete();
        
        string ComposeFileName(string XaMediaId);
        string ClearDate(string StringToClear);
        string AddPlus(string StringToDecode);

    protected:

    public:

        XaMedia();
	~XaMedia();
};
#endif