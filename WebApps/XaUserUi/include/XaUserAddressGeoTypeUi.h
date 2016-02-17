#ifndef XAUSERADDRESSGEOTYPEUI_H
#define XAUSERADDRESSGEOTYPEUI_H

#include <XaLibAction.h>

class XaUserAddressGeoTypeUi : public XaLibAction {
	
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

        XaUserAddressGeoTypeUi();
        ~XaUserAddressGeoTypeUi();
};
#endif
