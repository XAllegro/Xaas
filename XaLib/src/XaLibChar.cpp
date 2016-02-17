#include <XaLibChar.h>
#include <XaLibBase.h>

#include <curl/curl.h>

XaLibChar::XaLibChar() {

};

string XaLibChar::ClearXmlEntitiesBasic(string StringToClear){

	int pos;

	pos=0;
	pos=StringToClear.find_first_of("&");
		
	if (pos!=-1){
		while(pos!=-1){
			StringToClear.replace(pos,1,"&amp;");
			pos=StringToClear.find_first_of("&",pos+5);
		}
	}
 
	pos=0;
	pos=StringToClear.find_first_of("<");

	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&lt;");
			pos=StringToClear.find_first_of("<",pos+4);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of(">");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&gt;");
			pos=StringToClear.find_first_of(">",pos+4);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of("'");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&apos;");
			pos=StringToClear.find_first_of("'",pos+6);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of("\"");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&quot;");
			pos=StringToClear.find_first_of("\"",pos+6);
		}
	}

	return StringToClear;
};

string XaLibChar::ClearMultiByteChars(string StringToClear){
	unsigned pos;
	int i1;
	int i2;
	int i3;
	int i4;
	int CharCode;
	string ClearedChar;

	pos=0;

	while (pos< StringToClear.size()) {
		i1 = StringToClear[pos];

		if (i1 < 0){
			i1=i1+256;
			if (i1 > 192) {
				i2 = StringToClear[pos+1];
				if (i1 >= 240) {
					i3 = StringToClear[pos+2];
					i4 = StringToClear[pos+3];
					CharCode= (i1 & 0x07) * 0x40000 + (i2 & 0x3F) * 0x1000 + (i3 & 0x3F) * 0x40 + (i4 & 0x3F);
					ostringstream ss;
					ss << CharCode;
					ClearedChar="&#";
					ClearedChar.append(ss.str());
					ClearedChar.append(";");
					StringToClear.replace(pos,4,ClearedChar);
					pos=pos+ClearedChar.size();
				} else {
					if (i1 >= 224) {
						i3 = StringToClear[pos+2];
						CharCode=(i1 & 0x0F) * 0x1000 + (i2 & 0x3F) * 0x40 + (i3 & 0x3F);
						ostringstream ss;
						ss << CharCode;
						ClearedChar="&#";
						ClearedChar.append(ss.str());
						ClearedChar.append(";");
						StringToClear.replace(pos,3,ClearedChar);
						pos=pos+ClearedChar.size();
					} else {
						CharCode=(i1 & 0x1F) * 0x40 + (i2 & 0x3F);
						ostringstream ss;
						ss << CharCode;
						ClearedChar="&#";
						ClearedChar.append(ss.str());
						ClearedChar.append(";");
						StringToClear.replace(pos,2,ClearedChar);
						pos=pos+ClearedChar.size();
					}
				}
			} else {

				StringToClear.replace(pos,1,"");
			}
		} else {
			pos++;
		}
	}

	return StringToClear;
}

string XaLibChar::ClearXmlFrimm(string StringToClear){

	unsigned pos;

	pos=0;
	pos=StringToClear.find_first_of("&");

	if (pos!=-1){
		while(pos!=-1){
			StringToClear.replace(pos,1,"&amp;");
			pos=StringToClear.find_first_of("&",pos+5);
		}
	}
 
	pos=0;
	pos=StringToClear.find_first_of("<");

	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&lt;");
			pos=StringToClear.find_first_of("<",pos+1);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of(">");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&gt;");
			pos=StringToClear.find_first_of(">",pos+1);
		}
	}
	
	pos=0;
	pos=StringToClear.find_first_of("'");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&apos;");
			pos=StringToClear.find_first_of("'",pos+1);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of("\"");
	
	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"&quot;");
			pos=StringToClear.find_first_of("\"",pos+1);
		}
	}

	pos=0;
	pos=StringToClear.find_first_of("#");

	if (pos!=-1){
		while(pos!=-1){
			StringToClear.replace(pos,1,"&#35;");
			pos=StringToClear.find_first_of("#",pos+5);
		}
	}

const int MAXITEMS = 25;

string CharToSearch[MAXITEMS]={
 "!","$","%","(",")","*","+",",","-",
 ".","/",":","=","?","@","[","\\","]",
 "^","_","`","{","|","}","~"};

string CharToChange[MAXITEMS]={
"&#33;","&#36;","&#37;","&#40;","&#41;","&#42;","&#43;","&#44;","&#45;",
"&#46;","&#47;","&#58;","&#61;","&#63;","&#64;","&#91;","&#92;","&#93;",
"&#94;","&#95;","&#96;","&#123;","&#124;","&#125;","&#126;"};

	for (int n=0;n<MAXITEMS;n++){

		pos=0;
		pos=StringToClear.find_first_of(CharToSearch[n]);
		
		if (pos!=-1){

			while (pos!=-1){
				StringToClear.replace(pos,1,CharToChange[n]);
				pos=StringToClear.find_first_of(CharToSearch[n],pos+1);
			}
		}
	}

return StringToClear;
};

string XaLibChar::ClearSqlEntities(string StringToClear){

	unsigned pos=StringToClear.find_first_of("\"");

	while (pos!=-1){
		StringToClear.replace(pos,1,"\\\"");
		pos=StringToClear.find_first_of("\"",pos+2);
	}

	pos=StringToClear.find_first_of("\\");

	while (pos!=-1){
		StringToClear.replace(pos,1,"\\\\");
		pos=StringToClear.find_first_of("\\",pos+2);
	}

return StringToClear;
};

string XaLibChar::UrlDecode(string StringToDecode) {

	CURL *curl= nullptr;
	char* url=(char*)StringToDecode.c_str();
	char* CharDecoded=curl_easy_unescape(curl,url,0,NULL);

	string StringDecoded;
	StringDecoded.assign(CharDecoded);

return StringDecoded;
};

string XaLibChar::UrlEncode(string StringToEncode) {

	CURL *curl= nullptr;
	char* url=(char*)StringToEncode.c_str();
	char* CharEncoded=curl_easy_escape(curl,url,0);

	string StringEncoded;
	StringEncoded.assign(CharEncoded);

return StringEncoded;
};

inline bool XaLibChar::is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
};

string XaLibChar::B64Decode(const string& StringToDecode) {

	string encoded_string=StringToDecode;
	static const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	
	size_t in_len = encoded_string.size();
	size_t i = 0;
	size_t j = 0;
	int in_ = 0;
	string char_array_4, char_array_3;
	string ret;

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {

		j=i++;
		char_array_4[j] = encoded_string[in_];
		in_++;
		
		if (i ==4) {

			for (i = 0; i <4; i++)
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));
				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++) {
					ret+=char_array_3[i];
				}
				i = 0;
			}
		
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));
			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++){ 
			ret+= char_array_3[j];
		}
	}
	return ret;
};

string XaLibChar::B64Encode(const string& StringToEncode) {

	static const char b64_charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	string ret;
	unsigned char block_3[3];
	unsigned char block_4[4];
    
	
	int i=0, j=0,size;

	size = StringToEncode.size();

	string::const_iterator it;
	it=StringToEncode.begin();

	while(size--) {
		block_3[i++] = *it;
		if( i == 3 ){
			block_4[0] = (block_3[0] & 0xfc) >> 2;
			block_4[1] = ((block_3[0] & 0x03) << 4) + ((block_3[1] & 0xf0) >> 4);
			block_4[2] = ((block_3[1] & 0x0f) << 2) + ((block_3[2] & 0xc0) >> 6);
			block_4[3] = block_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++) {
				ret += b64_charset[block_4[i]];

			}
			i = 0;
		}
		it++;
	}

	if(i){
		for(j = i; j < 3; j++){
			block_3[j] = '\0';
		}
		block_4[0] = (block_3[0] & 0xfc) >> 2;
		block_4[1] = ((block_3[0] & 0x03) << 4) + ((block_3[1] & 0xf0) >> 4);
		block_4[2] = ((block_3[1] & 0x0f) << 2) + ((block_3[2] & 0xc0) >> 6);
		block_4[3] = block_3[2] & 0x3f;

		for(j = 0; (j < i + 1); j++){
			ret += b64_charset[block_4[j]];
		}
		while((i++ < 3)){
			ret += '=';
		}
	}
	return ret.c_str();
};


string XaLibChar::B64Encode(char* CharToEncode, int size) {

	static const char b64_charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	string ret;
	unsigned char block_3[3];
	unsigned char block_4[4];
    
	
	int i=0, j=0;

	int it=0;

	while(size--) {
		block_3[i++] = CharToEncode[it];
		if( i == 3 ){
			block_4[0] = (block_3[0] & 0xfc) >> 2;
			block_4[1] = ((block_3[0] & 0x03) << 4) + ((block_3[1] & 0xf0) >> 4);
			block_4[2] = ((block_3[1] & 0x0f) << 2) + ((block_3[2] & 0xc0) >> 6);
			block_4[3] = block_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++) {
				ret += b64_charset[block_4[i]];

			}
			i = 0;
		}
		it++;
	}

	if(i){
		for(j = i; j < 3; j++){
			block_3[j] = '\0';
		}
		block_4[0] = (block_3[0] & 0xfc) >> 2;
		block_4[1] = ((block_3[0] & 0x03) << 4) + ((block_3[1] & 0xf0) >> 4);
		block_4[2] = ((block_3[1] & 0x0f) << 2) + ((block_3[2] & 0xc0) >> 6);
		block_4[3] = block_3[2] & 0x3f;

		for(j = 0; (j < i + 1); j++){
			ret += b64_charset[block_4[j]];
		}
		while((i++ < 3)){
			ret += '=';
		}
	}
	return ret.c_str();
};

string XaLibChar::B64EncodeHexString(const string& StringToEncode) {
	
	string Decoded="";
	
	for (auto k=0;k<StringToEncode.size();k=k+2){
		
			int x = strtoul(StringToEncode.substr(k,2).c_str(), NULL, 16);

			char myChar = (char) x;
			Decoded=Decoded+myChar;
		}
		
		XaLibChar LibChar;
		return LibChar.B64Encode(Decoded);
};

string XaLibChar::imgBase64RemPlus(string StringToDecode) {

	unsigned posFrom=StringToDecode.find("base64");

	if (posFrom!=-1) {
	
		unsigned posTo=StringToDecode.find("\"",posFrom);
		unsigned pos=StringToDecode.find_first_of("+",posFrom);

		while (pos<=posTo){
			StringToDecode.replace(pos,1,"|");
			pos=StringToDecode.find_first_of("+",pos+1);
		}

		pos=0;
		pos=StringToDecode.find_first_of("+");

		while (pos!=-1){
			StringToDecode.replace(pos,1," ");
			pos=StringToDecode.find_first_of("+",pos+1);
		}

		pos=0;
		pos=StringToDecode.find_first_of("|");

		while (pos!=-1){
			StringToDecode.replace(pos,1,"+");
			pos=StringToDecode.find_first_of("|",pos+1);
		}

		return StringToDecode;

	} else {

		return RemovePlus(StringToDecode);

	}
};

void XaLibChar::RemoveCarriageReturn(string& InputString) {

	unsigned pos=InputString.find_first_of("\n");

	while (pos!=-1){
		InputString.replace(pos,1,"");
		pos=InputString.find_first_of("\n",pos+1);
	}

};

string XaLibChar::RemovePlus(string StringToDecode) {

	unsigned pos=StringToDecode.find_first_of("+");

	while (pos!=-1){
		StringToDecode.replace(pos,1," ");
		pos=StringToDecode.find_first_of("+",pos+1);
	}

return StringToDecode;
};

string XaLibChar::RemoveSpaceChar(string StringToDecode) {
	int pos;

	pos=0;
	pos=StringToDecode.find("&#160;");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"");
			pos=StringToDecode.find("&#160;",pos+1);
		}

	}

	pos=0;
	pos=StringToDecode.find("&#32;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,5,"");
			pos=StringToDecode.find("&#32;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&nbsp;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"");
			pos=StringToDecode.find("&nbsp;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find_first_of("\n");
		
	if (pos!=-1){
		while(pos!=-1){
			StringToDecode.replace(pos,1,"");
			pos=StringToDecode.find_first_of("\n",pos+1);
		}
	}
 
	pos=0;
	pos=StringToDecode.find_first_of("\r");

	if (pos!=-1){
		while (pos!=-1){
			StringToDecode.replace(pos,1,"");
			pos=StringToDecode.find_first_of("\r",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("\t");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,2,"");
			pos=StringToDecode.find("\t",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("    ");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,4," ");
			pos=StringToDecode.find("    ",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("   ");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,3," ");
			pos=StringToDecode.find("   ",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("  ");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,2," ");
			pos=StringToDecode.find("  ",pos+1);
		}
	}

return StringToDecode;
};

string XaLibChar::RemoveEmptyspace(string StringToDecode) {
	int pos;

	pos=0;
	pos=StringToDecode.find(" - ");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToDecode.replace(pos,3,"-");
			pos=StringToDecode.find(" - ",pos+1);
		}

	}

	pos=0;
	pos=StringToDecode.find(" ");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,1,"-");
			pos=StringToDecode.find(" ",pos+1);
		}
	}

return StringToDecode;
};

string XaLibChar::ClearChars(string StringToClear){
	unsigned pos;
	int i1;
	int i2;
	int i3;
	int CharCode;
	string ClearedChar;
	
	pos=0;

	while (pos< StringToClear.size()) {
		i1 = StringToClear[pos];

		if (i1 < 0){
			i1=i1+256;
			if (i1 > 192) {
				i2 = StringToClear[pos+1];
				if (i1 > 224) {
					i3 = StringToClear[pos+2];
					CharCode=(i1 & 0x0F) * 0x1000 + (i2 & 0x3F) * 0x40 + (i3 & 0x3F);
					ostringstream ss;
					ss << CharCode;
					ClearedChar="&#";
					ClearedChar.append(ss.str());
					ClearedChar.append(";");
					StringToClear.replace(pos,3,ClearedChar);
					pos=pos+ClearedChar.size();
				} else {
					CharCode=(i1 & 0x1F) * 0x40 + (i2 & 0x3F);
					ostringstream ss;
					ss << CharCode;
					ClearedChar="&#";
					ClearedChar.append(ss.str());
					ClearedChar.append(";");
					StringToClear.replace(pos,2,ClearedChar);
					pos=pos+ClearedChar.size();
				}
			} else {

				StringToClear.replace(pos,1," ");
			}
		} else {
			pos++;
		}
	}

	return StringToClear;
}

string XaLibChar::UnclearToNormalChar(string StringToDecode) {
	int pos;

	pos=0;
	pos=StringToDecode.find("&#39;");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToDecode.replace(pos,5,"");
			pos=StringToDecode.find("&#39;",pos+1);
		}

	}

	pos=0;
	pos=StringToDecode.find("&#224;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"a");
			pos=StringToDecode.find("&#224;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#242;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"o");
			pos=StringToDecode.find("&#242;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#46;");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToDecode.replace(pos,5,"");
			pos=StringToDecode.find("&#46;",pos+1);
		}

	}
	
	pos=0;
	pos=StringToDecode.find("&#236;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"i");
			pos=StringToDecode.find("&#236;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#249;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"u");
			pos=StringToDecode.find("&#249;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#232;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"e");
			pos=StringToDecode.find("&#232;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#233;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"e");
			pos=StringToDecode.find("&#233;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&#231;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"c");
			pos=StringToDecode.find("&#231;",pos+1);
		}
	}
	
	pos=0;
	pos=StringToDecode.find("&apos;");
	
	if (pos !=-1) {
		
		while (pos!=-1){
			
			StringToDecode.replace(pos,6,"&#39;");
			pos=StringToDecode.find("&apos;",pos+1);
		}
	}

return StringToDecode;
};

string XaLibChar::RemoveNs(string StringToDecode) {

	unsigned pos=StringToDecode.find("ns:");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToDecode.erase (pos,3);
			pos=StringToDecode.find("ns:",pos+1);
		}

	}

	unsigned pos1=StringToDecode.find(":ns");
	
	if (pos !=-1) {
		
		while (pos1!=-1){
			
			StringToDecode.erase (pos,3);
			pos=StringToDecode.find(":ns",pos+1);
		}
	}

return StringToDecode;
};
	
void XaLibChar::ClearReturn(string& StringToClear) {

	int pos;

	pos=0;
	pos=StringToClear.find_first_of("\n");
		
	if (pos!=-1){
		while(pos!=-1){
			StringToClear.replace(pos,1,"");
			pos=StringToClear.find_first_of("\n",pos+1);
		}
	}
 
	pos=0;
	pos=StringToClear.find_first_of("\r");

	if (pos!=-1){
		while (pos!=-1){
			StringToClear.replace(pos,1,"");
			pos=StringToClear.find_first_of("\r",pos+1);
		}
	}
};

void XaLibChar::ClearSpace(string& StringToClear) {

	int pos;

	pos=0;
	pos=StringToClear.find_first_of(" ");
		
	if (pos!=-1){
		while(pos!=-1){
			StringToClear.replace(pos,1,"");
			pos=StringToClear.find_first_of(" ",pos);
		}
	}
 };

void XaLibChar::ClearSpaceXml(string& StringToClear) {

	//Remove before
	int posb=StringToClear.find_first_of(" ");
	int posb1=StringToClear.find_first_of("<");

	if (posb!=-1){
		while(posb!=-1 && posb<posb1){
			StringToClear.replace(posb,1,"");
			posb=StringToClear.find_first_of(" ",posb);
			posb1=posb1-1;
		}
	}
	
	//Remove intermediate and after the last tag
	int posi=StringToClear.find_first_of(">");
	int posi1=StringToClear.find_first_of(" ",posi);
	int posi2=StringToClear.find_first_of("<",posi);
	
	if (posi1!=-1){
		while(posi1!=-1){
			StringToClear.replace(posi+1,posi2-posi1,"");
	
			posi=StringToClear.find_first_of(">",posi+2);
			posi1=StringToClear.find_first_of(" ",posi);
			posi2=StringToClear.find_first_of("<",posi);
		}
	}

	
};

void XaLibChar::EscapeForJs(string& StringToEscape) {

	int pos=StringToEscape.find_first_of("\"");

	if (pos!=-1){
		while(pos!=-1){
			StringToEscape.replace(pos,1,"\\\"");
			pos=StringToEscape.find_first_of("\"",pos+2);
		}
	}
};
	
int XaLibChar::CountCharOccurrences(string String, string Char) {
	int pos=0;
	int count=0;

	pos=String.find(Char);
	
	if (pos !=-1) {
	
		while (pos!=-1){
		
			count++;
			pos=String.find(Char,pos+1);
		}

	}

	return count;
};

string XaLibChar::UnclearAmpersand(string StringToUnclear) {
	int pos;

	pos=0;
	pos=StringToUnclear.find("&amp;");
	
	if (pos !=-1) {
	
		while (pos!=-1){
			
			StringToUnclear.replace(pos,5,"&");
			pos=StringToUnclear.find("&amp;",pos+1);
		}

	}
	
	return StringToUnclear;
};

string XaLibChar::ClearFrimmDesc(string StringToClear){
	unsigned pos;
	int i0;
	int i1;
	int CharCode;
	string ClearedChar;

	pos=0;

	while (pos< StringToClear.size()) {
            
		i1 = StringToClear[pos];

		if (i1<0) {i1 = i1+256;};

			if (i1==10 || i1==13 || i1==9) {

				StringToClear.replace(pos,1,"");
				//pos=pos;

			} else if (i1==160 || i1==32){

				if (pos>0) {

					i0 = StringToClear[pos-1];
					if (i0<0) {i0 = i0+256;};

						if (i0==32 || i0==160) {
							StringToClear.replace(pos,1,"");
							//pos=pos;		

						} else {
							pos++;
						};

					} else {

						pos++;
					};

                } else {
                    pos++;
                }
	}

	pos=0;

	while (pos< StringToClear.size()) {

		i1 = StringToClear[pos];

		if (i1<0) {
			i1 = i1+256;
		};
                
		if (i1>127) {

			CharCode = i1;
			ostringstream ss;
			ss << CharCode;
			ClearedChar="&#";
			ClearedChar.append(ss.str());
			ClearedChar.append(";");
			StringToClear.replace(pos,1,ClearedChar);
			pos=pos+ClearedChar.size();

		} else {
			pos++;
		}
	}
        
	pos=0;
	pos=StringToClear.find("&#160;");
	
	if (pos !=-1) {
	
		while (pos!=-1){
	
			StringToClear.replace(pos,6," ");
			pos=StringToClear.find("&#160;",pos+1);
		}
	}

	return StringToClear;
};   
        
XaLibChar::~XaLibChar() {
};
