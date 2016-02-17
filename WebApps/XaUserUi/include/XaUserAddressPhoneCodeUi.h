#ifndef XAUSERADDRESSPHONECODEUI_H
#define XAUSERADDRESSPHONECODEUI_H

#include <XaLibAction.h>

class XaUserAddressPhoneCodeUi : public XaLibAction {
	
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

        XaUserAddressPhoneCodeUi();
        ~XaUserAddressPhoneCodeUi();
};
#endif
