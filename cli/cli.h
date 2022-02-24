#ifndef CLI_H
# define CLI_H

enum e_return {
	OK,
	ERR,
};

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void display_cli_manual(void);
void display_cli_opt_help(void);
int display_error_message(void);

#endif // CLI_H
