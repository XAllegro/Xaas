#include <XaLibCurl.h>

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {

	string data((const char*) ptr, (size_t) size * nmemb);
    *((stringstream*) stream) << data/*<< endl*/;
    return size * nmemb;
};

XaLibCurl::XaLibCurl() {
	curl = curl_easy_init();
};

string XaLibCurl::Call(const string& url) {

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");

	stringstream out;

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

	CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
		LOG.Write("ERR", __FILE__, __FUNCTION__,__LINE__,"Curl Error Performing Request -> "+FromCharToString(*curl_easy_strerror(res)));
		throw 701;
    }

	LOG.Write("INF", __FILE__, __FUNCTION__,__LINE__,"Curl Call Response -> "+out.str());

	string OutString=out.str();
	XaLibChar::RemoveCarriageReturn(OutString);
	return OutString;
}

XaLibCurl::~XaLibCurl() {
	curl_easy_cleanup(curl);
};