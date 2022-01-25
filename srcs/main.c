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
	char *cmd = NULL;

	while (1)
	{
		// remplacer par print_prompt() :
		print_prompt();
		if ((cmd = get_next_line(STDIN_FILENO)))
		{
			// fork
			// execute cmd
			// wait
			// update history
			// update last_exit_status

			ft_printf("%s", cmd);
		}
	}
}