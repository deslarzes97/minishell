#include "../includes/minishell.h"

static char *print_user()
{
	char	*user;

	user = ft_strdup(getenv("USER"));
	if (!user)
		exit(BUILTIN_FAILURE);
	ft_putstr_fd(user, 1);
	return (user);
}

static char *print_relative_dir()
{
	char	*absolute_dir;
	char	*home;
	int		len;
	char 	*custom;

	absolute_dir = getcwd(NULL, 0);					// get current dir (absolute format)
	if (!absolute_dir)
		exit(BUILTIN_FAILURE);
	home = getenv("HOME");							// get home dir (absolute format)
	if (!home)
		exit(BUILTIN_FAILURE);
	len = ft_strlen(home);
	custom = ft_strnstr(absolute_dir, home, len);	// si home est dans current dir
	if (custom)
	{
		write(1, "~", 1);							// on remplace home par ~
		if (absolute_dir != home)					// et si on est dans un sous-dossier de home
			ft_putstr_fd(&custom[len], 1);			// on rajoute le chemin vers ce sous-dossier
	}
	else											// sinon on est à la racine de home
		ft_putstr_fd(absolute_dir, 1);				// alors on print le current dir (absolute format)
	return (absolute_dir);
}

int	print_prompt(void)
{
	char	*user;
	char	*absolute_dir;

	absolute_dir = NULL;
	user = print_user();
	write(1, ":", 1);
	absolute_dir = print_relative_dir();
	ft_putstr_fd(" $ ", 1);
	free(user);
	free(absolute_dir);
	return (0);
}
