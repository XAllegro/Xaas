#ifndef XAMEDIA_H
#define XAMEDIA_H

#include <XaLibModel.h>

class XaMedia : public XaLibModel {

    private:
        
        void Dispatcher(const string &CalledEvent);
        
        void List();
	void Read();
        void Create();
        void Delete();

    protected:

    public:

        XaMedia();
	~XaMedia();
};
#endif