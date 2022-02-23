#include "mongoose.h"
#include "ft_waiter.h"

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
	if (method == GET)
		mg_http_reply(c, 200, "", "it works");
}

// mg_connection -> a single connection descriptor
static void ev_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	// casting ev_data because struct http_message contains a parsed HTTP request
	struct mg_http_message *req_info = (struct mg_http_message *)ev_data;

	if (ev == MG_EV_HTTP_MSG) {
		// use mJSON to send info
		if (mg_http_match_uri(req_info, "/"))
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"location\": %s}", "\"/cep/v2/\"");
		else if (mg_http_match_uri(req_info, "/cep/v2/*"))
			handle_method(c, req_info);
		else {
			mg_http_reply(c, 404, "", "");
			return ;
		}
	}
}

int main(void)
{
	t_waiter waiter; // event manager that holds all active connections

	mg_mgr_init(&waiter.mgr);
	mg_http_listen(&waiter.mgr, "https://0.0.0.0:8000", ev_handler, NULL); // Create listening connection
	for (;;)
		mg_mgr_poll(&waiter.mgr, 1000); // Block forever
	mg_mgr_free(&waiter.mgr); // close all connections, and free all resources
	return (0);
}
