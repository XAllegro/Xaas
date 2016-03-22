#ifndef XADOMAINUI_H
#define XADOMAINUI_H

#include <XaLibAction.h>

class XaDomainUi : public XaLibAction {
	
    private:
        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        
        void List();
        void ListAsOptions();

	void UpdateFrm();
	void Update();
        void Delete();
        
        void AddAttributes();

    protected:

    public:

        XaDomainUi();
        ~XaDomainUi();
};
#endif
