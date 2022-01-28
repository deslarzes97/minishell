#include "../includes/minishell.h"

static char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*slash;
	int		i;

	i = 0;
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	paths = ft_split(getenv("PATH") + 5, ':');
	i = -1;
	while (paths[++i])
	{
		slash = ft_strjoin(paths[i], "/");
		path = ft_strjoin(slash, cmd);
		free(slash);
		if (access(path, F_OK) == 0)
		{
			ft_free_arr(paths);
			return (path);
		}
		free(path);
	}
	ft_free_arr(paths);
	return (0);
}

static void	execution_error(char *cmd)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	write(2, "\n", 1);
	exit(127);
}

void	execute_cmd(char *cmd, char **env)
{
	char	**cmd_arg_list;
	char	*path;

	cmd_arg_list = ft_split_blank(cmd);
	path = find_path(cmd_arg_list[0]);
	if (path == NULL || execve(path, cmd_arg_list, env) == -1)
	{
		ft_free_arr(cmd_arg_list);
		free(path);
		execution_error(cmd);
	}
}

int ls(char *cmd, char **env)
{
	pid_t	child;

	child = fork();
	if (child == 0)
		execute_cmd(cmd, env);
	else
		waitpid(child, NULL, 0);
	return (0);
}
