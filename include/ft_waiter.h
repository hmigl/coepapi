#ifndef FT_WAITER_H
# define FT_WAITER_H

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

char *fetch_third_party_api(void);

#endif // FT_WAITER_H
