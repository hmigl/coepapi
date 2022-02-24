#include "coepapi.h"
# define URI_PLUS_CEP_SIZE 16

extern t_waiter waiter;

void get_info(struct mg_connection *c, struct mg_http_message *req_info)
{
	if (req_info->uri.len != URI_PLUS_CEP_SIZE)
		mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"mesage\": %s}", "\"invalid CEP\"");
	else {
		sprintf(waiter.cep, "%.*s", (int)req_info->uri.len - 8, req_info->uri.ptr + 8);
		sprintf(waiter.url, "%s/cep/v2/%s", BR_API, waiter.cep);
		client_role(c);
	}
}

int find_out_method(const char *method)
{
	if (!strncmp(method, "GET", 3))
		return (GET);
	return (0);
}

void handle_method(struct mg_connection *c, struct mg_http_message *req_info)
{
	int method = find_out_method(req_info->method.ptr);

	if (!method)
		mg_http_reply(c, 400, "", "");
	if (method == GET) {
		get_info(c, req_info);
	}
}
