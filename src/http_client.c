#include "coepapi.h"

extern t_waiter waiter;

void client_role(struct mg_connection *c)
{
	waiter.rmt_content = fetch_third_party_api();
	if (waiter.curl_status_code == 200) {
		sprintf(waiter.status, "200");
		mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\r\n", waiter.rmt_content);
	}
	else {
		sprintf(waiter.status, "404");
		mg_http_reply(c, 404, "Content-Type: application/json\r\n", "{\"message\": %s}", "\"invalid CEP\"");
	}
}
