#include "../../srcs/mini_shell.h"

int	cd_cmd(char *input)
{
    int status;
	char *home;

    home = NULL;
    while (*input && *input == ' ')
        input++;
    input+=2;
    while (*input && *input == ' ')
        input++;
    if (*input == '\0') {
        home = getenv("HOME");
        if (home == NULL) {
            ft_putstr_fd("cd: 'HOME' not set\n", STDERR_FILENO);
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
