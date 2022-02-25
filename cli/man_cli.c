#include "cli.h"

void display_cli_manual(void)
{
	printf("Usage: ./api-cli [OPTION]\n");
	printf("Try ./api-cli --help to see options\n");
	exit(1);
}

void display_cli_opt_help(void)
{
	printf("-a,    --all \tDisplay all log information\n");
	printf("-d,    --date\tPrint only the dates of requests\n");
	printf("-r[METHOD]   \tGet all requests made to an URI using a specified method\n");
	printf("--live       \tObtain live uptades of the requests\n");
	exit(0);
}
