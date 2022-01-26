#include "../includes/minishell.h"

int pwd(void)
{
	char *dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		exit(BUILTIN_FAILURE);
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
	return (0);
}
