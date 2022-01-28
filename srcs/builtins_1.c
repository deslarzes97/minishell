/* Thomas's builtins */

// pwd : ok
// cd : ok

// remarques:
// pour l'instant j'envoie toute la cmd dans ces builtins.
// a voir plus tard si le parther fera le job aussi pour les builtins  ...
// est-ce qu'on appelle le parther avant is_builtin ou l'inverse ?
// si d'abord parther, les builtins recevront les meme types de données que les commandes simples

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
int cd(char *cmd)
{
	char *dir;
	char **cmd_args;

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
	dir = cmd_args[0];
	
	// if (dir[0] != '/')
	//	cherche d'abord dans les directory enregistrés dans CDPATH
	
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		write(2, ": ", 2);
		ft_putstr_fd(dir, 2);
		write(2, "\n", 2);
		exit(BUILTIN_FAILURE);
	}
	ft_free_arr(cmd_args);
	return (0);
}
