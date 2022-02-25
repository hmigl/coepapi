#include "coepapi.h"
#include <curl/curl.h>

extern t_waiter waiter;

static size_t
write_callback(char *content, size_t elsize, size_t nmemb, char *userp)
{
	size_t realsize = elsize * nmemb;
	struct memory *mem = (struct memory *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {
		return (0);
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), content, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = '\0';
	return (realsize);
}

char *fetch_third_party_api(void)
{
	CURL *curl;
	CURLcode res;
	struct memory chunk = { .memory = NULL, .size = 0 };

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, waiter.url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&(chunk));
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "curl failed: %s\n", curl_easy_strerror(res));
		else
			curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &waiter.curl_status_code);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return (chunk.memory);
}
