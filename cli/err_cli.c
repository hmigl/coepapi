#include "cli.h"

int display_error_message(void)
{
	fprintf(stderr, "Not a valid argument, RTFM!\n");
	exit(ERR);
}
