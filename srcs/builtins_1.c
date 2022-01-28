/* Thomas's builtins */

// pwd : ok
// cd : ok

// remarques:
// pour l'instant j'envoie toute la cmd dans ces builtins.
// a voir plus tard si le parther fera le job aussi pour les builtins  ...
// est-ce qu'on appelle le parther avant is_builtin ou l'inverse ?
// si d'abord parther, les builtins recevront les meme types de données que les commandes simples

#include "../includes/minishell.h"

int ls(char *cmd, char **env)
{
	pid_t	child;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
	{
		printf("ERROR in pipe creation\n");
		exit(1);
	}
	// printf("fd[0]: %d\n", pipefd[0]);
	// printf("fd[1]: %d\n", pipefd[1]);
	child = fork();
	if (child != 0)
		printf("I'm the main process (%d) and I created child %d\n", getpid(), child);

	if (child == 0)
	{
		printf("I'm child process %d\n", getpid());
		printf("new fd: %d\n", dup2(pipefd[1], STDOUT_FILENO));	// PROBLEME ICI
		close(pipefd[0]);
		printf("TEST\n");
		execute_cmd(cmd, env);
	}
	else
	{
		// printf("new fd: %d\n", dup2(pipefd[0], STDIN_FILENO)); // PROBLEME ICI
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		printf("process terminé: %d\n", waitpid(child, NULL, 0));
	}
	return (0);
}

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
