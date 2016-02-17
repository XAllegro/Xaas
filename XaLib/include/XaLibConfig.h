#ifndef XALIBCONFIG_H
#define XALIBCONFIG_H

#include <XaLibBase.h>

extern XaSettings SETTINGS;

class XaLibConfig  : protected XaLibBase {

	private:

		void ParseParam(xmlDocPtr doc, xmlNodePtr cur);

	protected:

	public:
	
		XaLibConfig();
		void GetParams(string& ConfFile);

		~XaLibConfig();
};
#endif
