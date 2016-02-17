#ifndef XAUSERADDRESSMAILUI_H
#define XAUSERADDRESSMAILUI_H

#include <XaLibAction.h>

class XaUserAddressMailUi : public XaLibAction {
	
    private:
        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();
        
        void ListAsOptions();

	void UpdateFrm();
	void Update();
        void Delete();

    protected:

    public:

        XaUserAddressMailUi();
        ~XaUserAddressMailUi();
};
#endif
