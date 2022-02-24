#include "coepapi.h"

t_waiter waiter;

// mg_connection -> a single connection descriptor
static void
ev_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	// casting ev_data because struct http_message contains a parsed HTTP request
	struct mg_http_message *req_info = (struct mg_http_message *)ev_data;

	if (ev == MG_EV_HTTP_MSG) {
		if (mg_http_match_uri(req_info, "/cep/v2/*"))
			handle_method(c, req_info);

		else if (mg_http_match_uri(req_info, "/"))
			mg_http_reply(c, 200, "Content-Type: application/json\r\n", "{\"location\": %s}", "\"/cep/v2/\"");

		else
			mg_http_reply(c, 404, "", "");
	}
	else if (ev == MG_EV_ERROR)
		mg_http_reply(c, 500, "", "");
	(void)fn_data;
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
