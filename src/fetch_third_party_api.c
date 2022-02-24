#include "ft_waiter.h"

extern t_waiter waiter;

// content points to the received data, whose size is nmemb
static size_t
write_callback(char *content, size_t elsize, size_t nmemb, char *userp)
{
	size_t realsize = elsize * nmemb;
	struct memory *mem = (struct memory *)userp;

	char *ptr = realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr) {
		fprintf(stderr, "not enough memory...");
		return (0);
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), content, realsize);
	mem->size += realsize;
	// data passed was not null terminated
	mem->memory[mem->size] = 0;

	return (realsize);
}

char *fetch_third_party_api(void)
{
	CURL *curl;
	CURLcode res;
	// init, but no data at this point
	// but it will be grown as needed
	struct memory chunk = { .memory = NULL, .size = 0 };

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, waiter.url);
		// send all data to this function
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&(chunk));
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "curl failed: %s\n", curl_easy_strerror(res));
		} 
		curl_easy_cleanup(curl);
		//free(chunk.memory);
	}
	curl_global_cleanup();
	return (chunk.memory);
}
