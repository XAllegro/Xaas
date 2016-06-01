#ifndef XALIBGEO_H
#define XALIBGEO_H

#include <XaLibBase.h>
#include <XaLibLog.h>

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibGeo : protected XaLibBase {

    private:

    protected:

    public:

        XaLibGeo();
        ~XaLibGeo();

        static vector<string> GetCartesian(string& Latitude,string& Longitude);

};
#endif
