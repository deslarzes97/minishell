#include "../libft/libft.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	char *cmd = NULL;

	while (1)
	{
		// remplacer par print_prompt() :
		ft_printf("our prompt $");
		if ((cmd = get_next_line(STDIN_FILENO)))
		{
			// fork
			// execute cmd
			// wait



			ft_printf("%s", cmd);
		}
	}
}