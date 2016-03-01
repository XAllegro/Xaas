#ifndef XARBACROLEUI_H
#define XARBACROLEUI_H

#include <XaLibAction.h>

class XaRbacRoleUi : public XaLibAction {
	
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
        XaRbacRoleUi();
        ~XaRbacRoleUi();
};
#endif