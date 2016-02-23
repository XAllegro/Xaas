#ifndef XAUSERTYPEUI_H
#define XAUSERTYPEUI_H

#include <XaLibAction.h>

class XaUserTypeUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);

        void CreateFrm();
        void Create();
        void List();
		void ListAsOptions();
		void Read();
		void UpdateFrm();
		void Update();
		void Delete();

    protected:

    public:
        XaUserTypeUi();
        ~XaUserTypeUi();
};
#endif