#ifndef XARBACROLERXAUSERUI_H
#define XARBACROLERXAUSERUI_H

#include <XaLibAction.h>

class XaRbacRoleRXaUserUi : public XaLibAction {
	
    private:

        void Dispatcher(const string &CalledEvent);

        void CreateFrm();
        void Create();
        void List();
		void UpdateFrm();
		void Update();
		void Delete();

    protected:

    public:
        XaRbacRoleRXaUserUi();
        ~XaRbacRoleRXaUserUi();
};
#endif