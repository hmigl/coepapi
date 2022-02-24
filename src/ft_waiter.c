#include "ft_waiter.h"
// strlen("/cep/v2/") + 8
# define URI_PLUS_CEP_SIZE 16

t_waiter waiter;

void act_as_client(struct mg_connection *c)
{
	char *remote_content = fetch_third_party_api();

	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\r\n", remote_content);
}

void get_info(struct mg_connection *c, struct mg_http_message *req_info)
{
	if (req_info->uri.len != URI_PLUS_CEP_SIZE) {
		mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"mesage\": %s}", "\"invalid CEP\"");
	} else {
		// write cep
		sprintf(waiter.cep, "%.*s", req_info->uri.len - 8, req_info->uri.ptr + 8);
		// and complete url
		sprintf(waiter.url, "%s/cep/v2/%s", BR_API, waiter.cep);
		act_as_client(c);
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

	// 400 bad request - not able to understand
	if (!method)
		mg_http_reply(c, 400, "", "");
	if (method == GET) {
		get_info(c, req_info);
		//mg_http_reply(c, 200, "", "it works");
	}
}

// mg_connection -> a single connection descriptor
static void ev_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	// casting ev_data because struct http_message contains a parsed HTTP request
	struct mg_http_message *req_info = (struct mg_http_message *)ev_data;

	if (ev == MG_EV_HTTP_MSG) {
		// TODO: use mJSON to send info
		if (mg_http_match_uri(req_info, "/"))
			// TODO: send api documentation as response
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"location\": %s}", "\"/cep/v2/\"");
		else if (mg_http_match_uri(req_info, "/cep/v2/*"))
			handle_method(c, req_info);
		else
			mg_http_reply(c, 404, "", "");
	} else if (ev == MG_EV_ERROR)
		mg_http_reply(c, 500, "", "");
}

int main(void)
{
	mg_mgr_init(&waiter.mgr);
	mg_http_listen(&waiter.mgr, "https://0.0.0.0:8000", ev_handler, NULL); // Create listening connection
	for (;;)
		mg_mgr_poll(&waiter.mgr, 1000); // Block forever
	mg_mgr_free(&waiter.mgr); // close all connections, and free all resources
	return (0);
}
