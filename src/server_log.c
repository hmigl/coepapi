#include "coepapi.h"
#include <time.h>
# define LOG_PATH ".log/server_log"

extern t_waiter waiter;

// message -> request line + headers + body
void log_request(struct mg_http_message *req_info)
{
	time_t now = time(NULL);
	FILE *log_file = fopen(LOG_PATH, "a");

	if (!log_file) {
		fprintf(stderr, "Couldn't open file\n");
		return ;
	}
	fprintf(log_file, "Timestamp:\n%s", ctime(&now));
	fprintf(log_file, "Method:\tPATH:\t\tPROTOCOL:\n");
	fprintf(log_file, "%.*s \t", (int)req_info->method.len, req_info->method.ptr);
	fprintf(log_file, "%.*s ", (int)req_info->uri.len, req_info->uri.ptr);
	fprintf(log_file, "%.*s\n\n", (int)req_info->proto.len, req_info->proto.ptr);
	// TODO: fix status
	//fprintf(log_file, "Response status: %ld\n\n", waiter.response_code);
	fclose(log_file);
}
