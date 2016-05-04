#ifndef XARBACROLE_H
#define XARBACROLE_H

#include <XaLibModel.h>

class XaRbacRole : public XaLibModel {

    private:

		void Dispatcher(const string &CalledEvent);

        void Create();
		void List();
		void ListAsOptions();
		void Read();
		void ReadForUpdateFrm();
		void Update();
		void Delete();

	protected:

	public:

		XaRbacRole();
		~XaRbacRole();
};
#endif
