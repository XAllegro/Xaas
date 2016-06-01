#ifndef XALIBSTRUCT_H
#define XALIBSTRUCT_H

#include <XaLibBase.h>
#include <XaLibChar.h>
#include <XaLibHttp.h>
#include <XaLibLog.h>
#include <XaLibDb.h>
#include <XaLibDom.h>
#include <XaLibSql.h>
#include <XaLibCrypto.h>

extern XaLibLog LOG;
extern XaLibHttp HTTP;
extern XaLibDb DB_SESSION;
extern XaLibDb DB_READ;
extern XaLibDb DB_WRITE;
extern XaLibDb DB_LOG;

extern XaSession SESSION;
extern XaRequest REQUEST;
extern XaResponse RESPONSE;
extern XaSettings SETTINGS;

class XaLibStruct : protected XaLibBase {

    private:

    protected:
        
    public:
        XaLibStruct ();
        virtual ~XaLibStruct ();
};
#endif