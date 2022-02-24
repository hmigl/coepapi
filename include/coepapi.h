#ifndef COEPAPI_H
# define COEPAPI_H

# include "mongoose.h"
# include "mjson.h"
# include <curl/curl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# define BR_API "https://brasilapi.com.br/api"

struct s_api {
	struct mg_mgr mgr;
	char cep[9];
	char url[50];
	char *rmt_content;
	int content_len;
};
typedef struct s_api t_waiter;

struct memory {
	char *memory;
	size_t size;
};

enum e_methods {
	GET = 1,
	POST,
	PUT,
	DELETE,
};

/*
 * api (or http server)
 */
void handle_method(struct mg_connection *c, struct mg_http_message *req_info);
int find_out_method(const char *method);
void get_info(struct mg_connection *c, struct mg_http_message *req_info);

/*
 * http client
 */
void client_role(struct mg_connection *c);
char *fetch_third_party_api(void);

#endif // COEPAPI_H
