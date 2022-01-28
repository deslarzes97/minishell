/* Thomas's builtins */

// remarques:
// pour l'instant j'envoie toute la cmd dans ces builtins.
// a voir plus tard si le parther fera le job aussi pour les builtins  ... je pense que oui

#include "../includes/minishell.h"

int pwd(char *cmd)											// ici on sait que cmd = pwd'blank' ou pwd'\n'
{
	char *dir;

	while (*cmd != ' ' && *cmd != '\t' && *cmd != '\n')		// itère jusqu'au 1er blank ou au \n
		cmd++;
	while (*cmd == ' ' || *cmd == '\t')						// itère tous les blanks (=space/tab)
		cmd++;
	if (*cmd != '\n')										// si pas un newline -> trop d'arguments
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		exit(BUILTIN_FAILURE);
	}
	dir = getcwd(NULL, 0);
	if (!dir)
		exit(BUILTIN_FAILURE);
	ft_putstr_fd(dir, 1);
	write(1, "\n", 1);
	free(dir);
	return (0);
}


// A rajouter:
// If the shell variable CDPATH exists, it is used as a search path: each directory name in CDPATH is searched for directory, 
// with alternative directory names in CDPATH separated by a colon (‘:’). 
// If directory begins with a slash, CDPATH is not used.
// exemple : https://www.oreilly.com/library/view/bash-cookbook/0596526784/ch16s05.html

void	chdir_error(char *dir)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	write(2, ": ", 2);
	ft_putendl_fd(dir, 2);
}

int	mini_pwd(void)
{
	char *dir;

	dir = getcwd(NULL, 0);
	if (!dir)
		exit(BUILTIN_FAILURE);
	ft_putendl_fd(dir, 1);
	free(dir);
	return (1);
}

static int	cdpath_search(char *dir)
{
	char	**cdpaths;
	int		i;
	int		len;
	char	*cdpath_dir;
	int		permission;

	cdpaths = ft_split(getenv("CDPATH") + 7, ':');
	if (dir[0] == '/' || !cdpaths)
	{
		printf("NOCDPATH");
		return(0);
	}
	
	// si cdpath[i]+dir ET accès à cdpath[i]+dir OK -> chdir cdpath[i]+dir + print abs_path
	// si cdpath[i]+dir existe ET PAS ACCES
		// si chdir dir OK -> chdir dir + print abs_path
		// sinon print "cd: permission denied: folder"
	i = 0;
	while (cdpaths[i])
	{
		len = ft_strlen(cdpaths[i]);
		if (cdpaths[i][len - 1] != '/')					// check trailing '/'
		{
			cdpath_dir = ft_strjoin(cdpaths[i], "/");
		}
		cdpath_dir = ft_strjoin(cdpaths[i], dir);	// rajouter encore un / entre cdpath et dir
		printf("dir joined: %s\n", cdpaths[i]);
		if (chdir(cdpath_dir) == 0)
			return (mini_pwd());
		if (access(cdpath_dir, F_OK) == 0 && access(cdpath_dir, X_OK) == -1)
			permission = -1;
		free(cdpath_dir);
		i++;
	}
	if (permission == -1 && chdir(dir) == 0)
		return (mini_pwd());
	if (permission == -1)
	{
		printf("TEST: cdpadth_dir exists but permission denied\n");		// A MODIFIER
		return (-1);
	}
	return (0);
}

int cd(char *cmd)
{
	char	*dir;
	char	**cmd_args;
	int		cdpath;

	while (*cmd != ' ' && *cmd != '\t' && *cmd != '\n')		// itère jusqu'au 1er blank ou au \n
		cmd++;
	while (*cmd == ' ' || *cmd == '\t')						// itère tous les blanks (space et tab)
		cmd++;
	if (*cmd == '\n')										// si pas d'argument -> use $HOME 
	{
		dir = getenv("HOME");
		if (!dir)
			exit(BUILTIN_FAILURE);
		chdir(dir);
		return (0);
	}
	cmd_args = ft_split_blank(cmd);
	if (cmd_args[1] != NULL)								// check si trop d'argument FACULTATIF ? ("Any additional arguments following directory are ignored")
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		ft_free_arr(cmd_args);
		exit(BUILTIN_FAILURE);
	}
	dir = ft_strdup(cmd_args[0]);
	ft_free_arr(cmd_args);
	
	//	cherche d'abord dans les directories enregistrés dans le CDPATH
	cdpath = cdpath_search(dir);
	if (cdpath == -1)
	{
		free (dir);
		exit(BUILTIN_FAILURE);
	}
	if (cdpath == 1)
	{
		free (dir);
		return (0);
	}
	
	// sinon arg[0] == / OU cdpath == 0 et donc pas de cdpath
	if (chdir(dir) == -1)
	{
		chdir_error(dir);
		free (dir);
		exit(BUILTIN_FAILURE);
	}
	return (0);
}
