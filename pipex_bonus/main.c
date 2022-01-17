/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:41:11 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/17 23:17:46 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://github.com/thomasn8/pipex_bonus -> version sans commentaire

#include "pipex.h"

// read input from terminal STDIN 
// until a line containing ONLY the delimiter is seen 
// (source: BASH man)
static void	read_terminal_lines(char *limiter, int *pipefd)
{
	char	*line;
	char	*limiter_nl;
	int		len;

	limiter_nl = ft_strjoin(limiter, "\n");
	len = ft_strlen(limiter) + 1;
	while (1)										// LOOP INFINI : prog continue à read tant qu'on lui donne des lines via le terminal (= stdin ici)
	{
		line = get_next_line(STDIN_FILENO);			// dès que GNL read un newline sur STDIN, il renvoie la line dans la loop
		if (!line)
			break ;
		if (ft_strncmp(line, limiter_nl, len) == 0
			|| ft_strncmp(line, limiter, len) == 0)
		{
			free(limiter_nl);
			free(line);
			exit(EXIT_SUCCESS);						// si line contient le LIMITER, TERMINE la loop ET le child process. Le pipe contient tous les précédents write
		}
		write(pipefd[1], line, ft_strlen(line));	// si pas trouvé le LIMITER, write la line dans le pipe
		free(line);
	}
}

static void	pipe_terminal(char *limiter)
{
	pid_t	child;
	int		pipefd[2];

	if (pipe(pipefd) == -1)							// créer un nouveau pipe
		exit(UNPREDICTABLE_ERROR);
	child = fork();									// créer un child process
	if (child == -1)
		exit(UNPREDICTABLE_ERROR);
	if (child == 0)
	{
		if (close(pipefd[0]) == -1)					// ferme le côté read du pipe pour utiliser que le côté write
			exit(UNPREDICTABLE_ERROR);
		read_terminal_lines(limiter, pipefd);
	}
	else											// le main process utilise le même pipe comme input (en read)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1|| close(pipefd[1]) == -1)
			exit(UNPREDICTABLE_ERROR);
		waitpid(child, NULL, 0);					// pour continuer il attend un changement de statut du child process "pid"
	}
}

static void	pipe_process(char *cmd, char **envp)
{
	pid_t	child;
	int		pipefd[2];

	if (pipe(pipefd) == -1)							// créer un nouveau pipe
		exit(UNPREDICTABLE_ERROR);
	child = fork();									// créer un child process. A partir d'ici on a 2 process avec chacun sa mémoire indépendante (mémoire du main process dupliquée)
	// if (child != 0)
	// 	printf("I'm the main process (%d) and I created child %d\n", getpid(), child);
	if (child == -1)
		exit(UNPREDICTABLE_ERROR);
	if (child == 0)									// le child process utilise le pipe pour écrire dedans -> pipefd[1] = write
	{												// et ferme le côté inutilisé sinon le pipe se mettra en attente de read
		// printf("I'm child process %d\n", getpid());
		if (dup2(pipefd[1], STDOUT_FILENO) == -1 || close(pipefd[0]))
			exit(UNPREDICTABLE_ERROR);
		execute_cmd(cmd, envp);						// le child process est remplacé par un tout nouveau process d'execution (voir man execve)
	}												// avec pour stdout le pipe
	else
	{												// le main process utilise le pipe comme input -> pipefd[0] = read (et ferme le côté write)
		if (dup2(pipefd[0], STDIN_FILENO) == -1 || close(pipefd[1]))
			exit(UNPREDICTABLE_ERROR);
		waitpid(child, NULL, 0);					// pour continuer il attend un changement de statut du child process "pid"
	}
}

int	main(int ac, char **av, char **envp)
{
	int		files;
	t_file	infile;
	t_file	outfile;
	int		i;
	int		cmd_count;

	errno = 0;
	files = check_here_doc_param(ac, av, &infile, &outfile);
	get_files_fd(files, &infile, &outfile);
	if (files == 1)
		cmd_count = ac - 4;
	else
		cmd_count = ac -3;

													// POUR LA PREMIERE CMD
	if (files == 1)									// si here_doc :
		pipe_terminal(av[2]);						// on va lire le terminal en stdin à la place d'avoir un infile
	else
	{												// sinon :
		if (dup2(infile.fd, STDIN_FILENO) == -1)	// duplique le infile_fd et le redirige en stdin (fd = 0)
			exit(UNPREDICTABLE_ERROR);
	}


	i = 0;											// JUSQU'A L'AVANT-DERNIERE CMD (ycomprise)
	if (files == 1)
		i++;
	while (--cmd_count)								// split le process en 2 pour executer chaque nouvelle cmd dans un child p.
		pipe_process(av[2 + i++], envp);			// et récup l'output dans le pipe du main p. (stdout est constamment redirigé dans un pipe)


	if (dup2(outfile.fd, STDOUT_FILENO) == -1)		// POUR LA DERNIERE CMD
		exit(UNPREDICTABLE_ERROR);					// duplique le outfile_fd et le redirige en stdout (fd = 1)
	execute_cmd(av[ac - 2], envp);					// execute la derniere cmd avec outfile_fd en stdout
	return (0);
}

// man de execve :
// The argument envp is also a pointer to a null-terminated array of character pointers to null-terminated strings.
// A pointer to this array is normally stored in the global variable environ.

// envp reçoit automatiquement la liste des variables insérées manuellement + celle des variables d'environnement ?
