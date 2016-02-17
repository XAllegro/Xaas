#ifndef XAOUUI_H
#define XAOUUI_H

#include <XaLibAction.h>

class XaOuUi : public XaLibAction {
	
    private:
        void Dispatcher(const string &CalledEvent);
        void CreateFrm();
        void Create();

        void List();
        void ListAsOptions();

        void Tree();
        void Explorer();

		void Read();
		void UpdateFrm();
		void Update();

    protected:

    public:

        XaOuUi();
        ~XaOuUi();
};
#endif
