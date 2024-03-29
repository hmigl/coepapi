#include "cli.h"

static void
cli_live_mode(void)
{
	char buf[256];
	FILE *log = fopen("../.log/server_log", "r");
	if (!log) {
		fprintf(stderr, "Couldn't open file\n");
		exit(ERR);
	}
	while (fgets(buf, 256, log) != NULL)
		printf("%s", buf);
	fclose(log);
}

static void 
filter_specific_methods(char *method)
{
	if (!*method)
		exit(display_error_message());
	if (!strcmp(method, "GET"))
		system("grep GET ../.log/server_log");
	else if (!strcmp(method, "POST"))
		system("grep POST ../.log/server_log");
	else if (!strcmp(method, "PUT"))
		system("grep PUT ../.log/server_log");
	else if (!strcmp(method, "PATCH"))
		system("grep PATCH ../.log/server_log");
	else if (!strcmp(method, "DELETE"))
		system("grep DELETE ../.log/server_log");
	else
		exit(display_error_message());
}

static int
execute_cli_valid_commands(char *argv[])
{
	if (!strcmp(argv[1], "--all") || !strcmp(argv[1], "-a"))
		system("cat ../.log/server_log");
	else if (!strcmp(argv[1], "--date") || !strcmp(argv[1], "-d"))
		system("grep --regexp=^{Su,Mo,Tu,We,Th,Fr,Sa} ../.log/server_log");
	else if (!strncmp(argv[1], "-r", 2)) {
		char *method = argv[1] + 2;
		filter_specific_methods(method);
	}
	else if (!strcmp(argv[1], "--live")) {
		while (1) {
			cli_live_mode();
			sleep(3);
		}
	}
	else
		display_error_message();
	return (OK);
}

/*
 * Filter data or modify 'api-cli' default behavior
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
		display_cli_manual();
	if (!strcmp(argv[1], "--help"))
		display_cli_opt_help();
	if (execute_cli_valid_commands(argv) == ERR)
		display_error_message();
	return (OK);
}
