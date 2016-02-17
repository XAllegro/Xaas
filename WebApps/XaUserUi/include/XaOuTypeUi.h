#ifndef XAOUTYPEUI_H
#define XAOUTYPEUI_H

#include <XaLibAction.h>

class XaOuTypeUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        void List();
        void ListAsOptions();

    protected:

    public:
        XaOuTypeUi();
        ~XaOuTypeUi();
};
#endif