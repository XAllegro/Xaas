#ifndef XAUSERADDRESSGEOUI_H
#define XAUSERADDRESSGEOUI_H

#include <XaLibAction.h>

class XaUserAddressGeoUi : public XaLibAction {
	
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

        XaUserAddressGeoUi();
        ~XaUserAddressGeoUi();
};
#endif
