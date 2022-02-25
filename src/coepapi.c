#include "coepapi.h"

t_waiter waiter;

static void
ev_handler(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_message *req_info = (struct mg_http_message *)ev_data;

	if (ev == MG_EV_HTTP_MSG) {
		if (mg_http_match_uri(req_info, "/cep/v2/*"))
			handle_method(c, req_info);
		else if (mg_http_match_uri(req_info, "/") && !strncmp(req_info->method.ptr, "GET", 3)) {
			sprintf(waiter.status, "200");
			mg_http_reply(c, 200,"Content-Type: application/json\r\n", "{\"location\": %s}", "\"/cep/v2/\"");
		}
		else {
			sprintf(waiter.status, "404");
			mg_http_reply(c, 404, "", "");
		}
		log_request(req_info);
	}
	else if (ev == MG_EV_ERROR) {
		sprintf(waiter.status, "500");
		mg_http_reply(c, 500, "", "");
	}
	(void)fn_data;
}

int main(void)
{
	mg_mgr_init(&waiter.mgr);
	mg_http_listen(&waiter.mgr, LISTENADD, ev_handler, NULL);
	for (;;)
		mg_mgr_poll(&waiter.mgr, 1000);
	mg_mgr_free(&waiter.mgr);
	return (0);
}
