#ifndef FT_WAITER_H
# define FT_WAITER_H

#include "mongoose.h"
#include <stdlib.h>
#include <stdio.h>

struct s_api {
	struct mg_mgr mgr;
};
typedef struct s_api t_waiter;

enum e_methods {
	GET = 1,
	POST,
	PUT,
	DELETE,
};

#endif
