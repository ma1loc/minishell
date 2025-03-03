#include "../../srcs/mini_shell.h"

int	cd_cmd(char *input)
{
    int status;
	char *home;

	// printf("input -> %s\n", input);
    while (*input && *input == ' ')
        input++;
	if (ft_strncmp(input, "cd", 2) == 0)
		input+=2;
    while (*input && *input == ' ')
        input++;
    if (*input == '\0') {
        home = getenv("HOME");
        if (home == NULL) {
            ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
            return 1;
        }
        status = chdir(home);
    } else
        status = chdir(input);
    if (status == -1) {
		perror("cd");
        return 1;
    }
    return 0;
}
