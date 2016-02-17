#ifndef XAPAGES_H
#define XAPAGES_H

#include <XaLibAction.h>

class XaPages : public XaLibAction {

    private:

        void Dispatcher(const string &CalledEvent);
        void XaMyPage();
        void WsLogList();

    protected:

    public:

        XaPages();
        ~XaPages();
};
#endif