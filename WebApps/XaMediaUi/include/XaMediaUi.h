#ifndef XAMEDIAUI_H
#define XAMEDIAUI_H

#include <XaLibAction.h>

class XaMediaUi : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);

        void List();
	void Read();
        void CreateFrm();
        void Create();
        void Delete();

    protected:

    public:

        XaMediaUi();
        ~XaMediaUi();
};
#endif