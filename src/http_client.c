#include "coepapi.h"

extern t_waiter waiter;

void client_role(struct mg_connection *c)
{
	waiter.rmt_content = fetch_third_party_api();
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\r\n", waiter.rmt_content);
}
