/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:41:11 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/16 21:19:12 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	usage(void)
{
	ft_putstr_fd("Usage : ./pipex input_file cmd1 cmd2 [...] output_file\n", 2);
	exit(UNPREDICTABLE_ERROR);
}

static void	execution_error(char *cmd)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	exit (EXEC_ERROR);
}

void	execute_cmd(char *cmd, char **envp)
{
	char	**cmd_arg_list;
	char	*path;

	cmd_arg_list = ft_split(cmd, ' ');
	path = find_path(cmd_arg_list[0], envp);
	if (path == NULL || execve(path, cmd_arg_list, envp) == -1)
	{
		ft_free_arr(cmd_arg_list);
		free(path);
		execution_error(cmd);
	}
}

void	split_process(char *cmd, char **envp)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit(UNPREDICTABLE_ERROR);
	pid = fork();
	if (pid != 0)
		printf("I'm the main process (%d) and I created child %d\n", getpid(), pid);
	if (pid == -1)
		exit(UNPREDICTABLE_ERROR);
	if (pid == 0)
	{
		printf("I'm child process %d\n", getpid());
		if (dup2(pipefd[1], STDOUT_FILENO) == -1 || close(pipefd[0]))
			exit(UNPREDICTABLE_ERROR);
		execute_cmd(cmd, envp);
	}
	else
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1 || close(pipefd[1]))
			exit(UNPREDICTABLE_ERROR);
		waitpid(pid, NULL, 0);
	}
}

// man de execve :
// The argument envp is also a pointer to a null-terminated array of character pointers to null-terminated strings.
// A pointer to this array is normally stored in the global variable environ.
int	main(int ac, char **av, char **envp)	// envp reçoit automatiquement les variables ?
{
	int		infile_fd;
	int		outfile_fd;
	int		i;
	int		cmd_count;

	errno = 0;
	if (ac < 5)
		usage();
	get_files_fd(av[1], av[ac - 1], &infile_fd, &outfile_fd);
	i = 0;
	while (av[i])
		i++;
	cmd_count = i - 3;
	if (dup2(infile_fd, STDIN_FILENO) == -1)
		exit(UNPREDICTABLE_ERROR);
	i = 0;
	while (i < cmd_count - 1)
		split_process(av[2 + i++], envp);
	if (dup2(outfile_fd, STDOUT_FILENO) == -1)
		exit(UNPREDICTABLE_ERROR);
	execute_cmd(av[ac - 2], envp);
	return (0);
}
