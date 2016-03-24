#ifndef XAUSERTYPE_H
#define XAUSERTYPE_H

#include <XaLibModel.h>

class XaUserType : public XaLibModel {

    private:
		
		void Dispatcher(const string &CalledEvent);
		
        void GetXmlModel();
		void Create();
		void List();
		void ListAsOptions();
		void Read();
		void ReadForUpdateFrm();
		void Update();
		void Delete();

	protected:

	public:

		XaUserType();		
		~XaUserType();

};
#endif
