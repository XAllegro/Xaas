#ifndef XALIBGUI_H
#define XALIBGUI_H

#include <XaLibBase.h>
#include <XaLibLog.h>
#include <XaLibChar.h>
#include <XaLibDom.h>
#include <XaLibXsl.h>

class XaLibGui : protected XaLibBase {

    private:

    protected:

    public:

        static string CreateForm(const vector<string>& XmlFiles, const vector<string>& XmlStrings,const vector<string>& XslFiles,const vector<string>& XslStrings,const vector<string>& XslParams);
        static string CreateList(DbResMap ResMap,const vector<string>& TagNames,const string& RootTagName,const string& GroupTagName);

        XaLibGui();
        ~XaLibGui();
};
#endif
