#include "coepapi.h"
# define LOG_PATH ".log/server_log"

extern t_waiter waiter;

void log_request(struct mg_http_message *req_info)
{
	time_t now = time(NULL);
	FILE *log_file = fopen(LOG_PATH, "a");
	if (!log_file) {
		fprintf(stderr, "Couldn't open file\n");
		return ;
	}
	fprintf(log_file, "Request timestamp:\n%s", ctime(&now));
	fprintf(log_file, "%.*s  ", (int)req_info->method.len, req_info->method.ptr);
	fprintf(log_file, "%.*s\n", (int)req_info->uri.len, req_info->uri.ptr);
	fprintf(log_file, "Response status: %d\n\n", atoi(waiter.status));
	fclose(log_file);
}
