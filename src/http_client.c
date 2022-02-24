#include "coepapi.h"

void client_role(struct mg_connection *c)
{
	char *remote_content = fetch_third_party_api();
	mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\r\n", remote_content);
}
