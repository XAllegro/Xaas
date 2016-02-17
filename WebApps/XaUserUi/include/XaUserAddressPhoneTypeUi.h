#ifndef XAUSERADDRESSPHONETYPEUI_H
#define XAUSERADDRESSPHONETYPEUI_H

#include <XaLibAction.h>

class XaUserAddressPhoneTypeUi : public XaLibAction {
	
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

        XaUserAddressPhoneTypeUi();
        ~XaUserAddressPhoneTypeUi();
};
#endif
