#ifndef XALIBERROR_H
#define XALIBERROR_H

#include <XaLibBase.h>

class XaLibError : protected XaLibBase {

    private:

		map<int,string> XaErrors;

	protected:

	public:

		void Setup();
		string GetError(const int& ErrorCode);

		XaLibError();
		~XaLibError();
};
#endif