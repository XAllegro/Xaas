#ifndef XAMEDIADATAUI_H
#define XAMEDIADATAUI_H

#include <XaLibAction.h>

class XaMediaDataUi : public XaLibAction {

    private:

		void Dispatcher(const string &CalledEvent);

        void List();
		void Read();
        void CreateFrm();
        void Create();
        void Update();
        void UpdateFrm();
        void Delete();

    protected:

    public:

        XaMediaDataUi();
        ~XaMediaDataUi();
};
#endif