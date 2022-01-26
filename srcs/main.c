#include "../includes/minishell.h"

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
			
			// POUR TESTER (A ENLEVER APRES) :
			// ft_printf("%s", cmd);
			if (ft_strncmp(cmd, "pwd ", 4) == 0 || ft_strncmp(cmd, "pwd\n", 4) == 0)
				pwd();
			/////////////////////////

			free(cmd);
		}
	}
}