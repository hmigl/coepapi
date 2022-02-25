#ifndef COEPAPI_H
# define COEPAPI_H

# include "mongoose.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# define BR_API "https://brasilapi.com.br/api"
# define LISTENADD "http://0.0.0.0:8000"

struct s_api {
	struct mg_mgr mgr;
	char cep[9];
	char url[50];
	char *rmt_content;
	long curl_status_code;
	char status[4];
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

/*
 * log
 */
void log_request(struct mg_http_message *req_info);

#endif // COEPAPI_H
