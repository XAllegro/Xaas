#ifndef XAPAGES_H
#define XAPAGES_H

#include <XaLibAction.h>

class XaPages : public XaLibAction {

    private:

        void XaMyPage();
        void Dispatcher(const string &CalledEvent);

    protected:

    public:

        XaPages();
        ~XaPages();

};
#endif