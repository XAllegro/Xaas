#ifndef XALIBCHAR_H
#define XALIBCHAR_H

#include <XaLibBase.h>

class XaLibChar : protected XaLibBase {

	private:

		static inline bool is_base64(unsigned char c);

	protected:

	public:

		XaLibChar();
		~XaLibChar();
		
		string ClearMultiByteChars(string StringToClear);
		string ClearXmlEntitiesBasic(string StringToClear);
		string ClearXmlFrimm(string StringToClear);
		string ClearSqlEntities(string StringToClear);

		static void RemoveCarriageReturn(string& InputString);
		string RemovePlus(string StringToDecode);
		
		string imgBase64RemPlus(string StringToDecode);
		string UrlDecode(string StringToDecode);
		string UrlEncode(string StringToEncode);

		string B64Decode(const string& StringToDecode);
		string B64Encode(const string& StringToEncode);
		string B64EncodeHexString(const string& StringToEncode);
		
		string B64Encode(char * CharToEncode, int size);

		static void ClearReturn(string& StringToClear);
		static void ClearSpace(string& StringToClear);
                static void ClearSpaceXml(string& StringToClear);
                static void EscapeForJs(string& StringToEscape);
                

                
		string RemoveNewLine(string StringToDecode);
		string RemoveNs(string StringToDecode);
		string RemoveEmptyspace(string StringToDecode);
		string RemoveSpaceChar(string StringToDecode);
		string UnclearToNormalChar(string StringToDecode);
        string ClearCarriageReturn(string StringToClear);
        string ClearChars(string StringToClear);
        string ClearFrimmDesc(string StringToClear);
        int CountCharOccurrences(string String, string Char);
        string UnclearAmpersand(string StringToUnClear);
};
#endif
