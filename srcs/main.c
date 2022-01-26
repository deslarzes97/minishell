#include "../includes/minishell.h"

int	print_prompt(void)
{
	ft_putstr_fd(CYA,1);
	ft_putstr_fd("a different prompt ≠ ",1);
	ft_putstr_fd(WHI,1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)	av;
	(void)	env;
	char	*cmd;
	
	while (1)
	{
		cmd = NULL;
		print_prompt();

		// utiliser signal ou sigaction pour détecter ctrl-d ctrl-c
		cmd = get_next_line(STDIN_FILENO);
		if (cmd)	// le call à GNL sur STDIN_FILENO provoque une pause (en attente de return) dans la loop infinie
		{
			// fork a subshell / pipex
			// execute cmd
			// wait
			// update history
			// update last_exit_status
			ft_printf("%s", cmd);	// A ENLEVER APRES
			free(cmd);
		}
	}
}