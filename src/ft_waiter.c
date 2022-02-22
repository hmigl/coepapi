#include "mongoose.h"
#include "ft_waiter.h"

// mg_connection -> a single connection descriptor
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	struct mg_http_serve_opts opts = {.root_dir = "."};   // Serve local dir
	if (ev == MG_EV_HTTP_MSG) mg_http_reply(c, 200, "Content type: text/plain\r\n",
			"hello, world", "");
		//mg_http_serve_dir(c, ev_data, &opts);
}

int main(void)
{
	struct mg_mgr mgr; // event manager that holds all active connections

	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, "https://0.0.0.0:8000", fn, NULL); // Create listening connection
	for (;;) mg_mgr_poll(&mgr, 1000); // Block forever
	mg_mgr_free(&mgr); // close all connections, and free all resources
	return (0);
}
