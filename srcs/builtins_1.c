/* Thomas's builtins */

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

int cd(char *cmd)											// ici on sait que cmd = cd'blank' ou cd'\n'
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

	// some tests :
	// chdir("/Users/thomas/Downloads");
	// chdir("/Users/thomas");
	// chdir("../amyplant");

	// enregistre 1er arg dans dir
	// check si il y a encore d'autre args
	// si oui -> erreur
	// si non 
		// check si dir est un path absolute ou relative grace au / initial
		// gérer le(s) '..' dans le path ?
		// check les accès a dir ?
		// chdir(dir)
	cmd_args = ft_split_blank(cmd);
	if (cmd_args[1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		ft_free_arr(cmd_args);
		exit(BUILTIN_FAILURE);
	}
	if (cmd_args[0][0] == '/')	// path = absolute
	{

	}
	else						// path = relative
	{

	}
	ft_free_arr(cmd_args);
	return (0);
}
