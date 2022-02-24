#include "coepapi.h"
#include <time.h>
# define LOG_PATH ".log/server_log"

// message -> request line + headers + body
void log_request(struct mg_http_message *req_info)
{
	time_t now = time(NULL);
	FILE *log_file = fopen(LOG_PATH, "a");

	if (!log_file) {
		fprintf(stderr, "Couldn't open file\n");
		return ;
	}
	fprintf(log_file, "%s", ctime(&now));
	fprintf(log_file, "%s\n", req_info->message.ptr);
	fclose(log_file);
}
