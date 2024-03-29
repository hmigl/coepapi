#include "coepapi.h"
# define URI_PLUS_CEP_SIZE 16

extern t_waiter waiter;

void get_info(struct mg_connection *c, struct mg_http_message *req_info)
{
	if (req_info->uri.len != URI_PLUS_CEP_SIZE) {
		sprintf(waiter.status, "404");
		mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"message\": %s}", "\"invalid CEP\"");
	}
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
	if (!strncmp(method, "POST", 4))
		return (POST);
	if (!strncmp(method, "PUT", 3))
		return (PUT);
	if (!strncmp(method, "DELETE", 6))
		return (DELETE);
	return (0);
}

void handle_method(struct mg_connection *c, struct mg_http_message *req_info)
{
	int method = find_out_method(req_info->method.ptr);

	if (!method) {
		sprintf(waiter.status, "400");
		mg_http_reply(c, 400, "", "");
	}
	if (method == GET)
		get_info(c, req_info);
	else {
		sprintf(waiter.status, "405");
		mg_http_reply(c, 405, "", "");
	}
}
