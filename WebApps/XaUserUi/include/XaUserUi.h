#ifndef XAUSERUI_H
#define XAUSERUI_H

#include <XaLibAction.h>

class XaUserUi : public XaLibAction {
	
    private:

		void Dispatcher(const string &CalledEvent);

		void List();
		void Read();
		void CreateFrm();
		void Create();
		void UpdateFrm();
		void Update();
		void Delete();


	protected:


	public:

		XaUserUi();
		//virtual int Authenticate(string StrEmail,string StrPassword);
		virtual ~XaUserUi();
	
};
#endif
