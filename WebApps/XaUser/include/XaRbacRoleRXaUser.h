#ifndef XARBACROLERXAUSER_H
#define XARBACROLERXAUSER_H

#include <XaLibModel.h>

class XaRbacRoleRXaUser : public XaLibModel {

    private:
		
		void Dispatcher(const string &CalledEvent);
		
        void GetXmlModel();
		void Create();
		void List();
		void ReadForUpdateFrm();
		void Update();
		void Delete();

	protected:

	public:

		XaRbacRoleRXaUser();		
		~XaRbacRoleRXaUser();

};
#endif
