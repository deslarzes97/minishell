#include "../includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)	ac;
	(void)	av;
	(void)	env;
	char	*cmd;
	
	// signal (ou sigaction) pour détecter ctrl+c / ctrl+d (ou détecter dans gnl ?)
	while (1)
	{
		cmd = NULL;
		print_prompt();
		cmd = get_next_line(STDIN_FILENO);
		if (cmd)	// le call à GNL sur STDIN_FILENO provoque une pause (en attente de return) dans la loop infinie
		{
			// parther() + is_builtin(cmd)?

				// si OUI: traiter la cmd spécifiquement comme un builtin
				// est-ce qu'on execute les builtins sans fork ? (cad dans le main process)
				
				// si NON: fork (voir pipex)
				// child_process
					// -> execute cmd
				// parent_process
					// -> wait exit status
					// (update history)
					// (if | update $?)
			


			/* POUR TESTER LES BUILTINS (A ENLEVER APRES) */
			if (ft_strncmp(cmd, "pwd ", 4) == 0 || ft_strncmp(cmd, "pwd\t", 4) == 0 || ft_strncmp(cmd, "pwd\n", 4) == 0)
				pwd(cmd);
			if (ft_strncmp(cmd, "cd ", 3) == 0 || ft_strncmp(cmd, "cd\t", 3) == 0 || ft_strncmp(cmd, "cd\n", 3) == 0)
				cd(cmd);
			/* ***************************** */


			free(cmd);
		}
	}
}
