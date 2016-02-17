#ifndef XALIBCRYPTO_H
#define XALIBCRYPTO_H

#include <XaLibBase.h>
#include <XaLibLog.h>


#if OPENSSL_VERSION_NUMBER >= 0x0090808fL
#define LIBSSH2_AES_CTR 0
#else
#define LIBSSH2_AES_CTR 1
#endif

extern XaLibLog LOG;
extern XaSettings SETTINGS;

class XaLibCrypto : protected XaLibBase {

	private:

	protected:

	public:

		XaLibCrypto();
		~XaLibCrypto();

		static string GetSha1(const string& WordToCrypt);
		static string GetSha2(const string& WordToCrypt);

		string AesEncrypt(const string& StringToEncrypt);
		string AesEncrypt(const string& StringToEncrypt, const string& EncryptionKey);

		string AesDecrypt(const string& EncryptedValue);
		string AesDecrypt(const string& EncryptedValue, const string& EncryptionKey);

		string AesEncryptCtr(const string& StringToEncrypt, const string& EncryptionKey, const string& EncryptionIV);
		string AesDecryptCtr(const string& EncryptedValue, const string& EncryptionKey, const string& EncryptionIV);
};
#endif
