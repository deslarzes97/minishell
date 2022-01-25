#include "../includes/minishell.h"

int	print_prompt(void)
{
	ft_putstr_fd(CYA,1);
	ft_putstr_fd("bullshit prompt ≠ ",1);
	ft_putstr_fd(WHI,1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	char *cmd;

	while (1)
	{
		cmd = NULL;
		print_prompt();
		cmd = get_next_line(STDIN_FILENO);
		if (cmd)	// le call à GNL sur STDIN_FILENO provoque une pause dans la loop infinie
		{
			// fork
			// execute cmd
			// wait
			// update history
			// update last_exit_status
			ft_printf("%s", cmd);	// A ENLEVER APRES
			free(cmd);
		}
	}
}