#ifndef XAUSERADDRESSPHONEUI_H
#define XAUSERADDRESSPHONEUI_H

#include <XaLibAction.h>

class XaUserAddressPhoneUi : public XaLibAction {
	
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

        XaUserAddressPhoneUi();
        ~XaUserAddressPhoneUi();
};
#endif
