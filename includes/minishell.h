#ifndef MINISHELL_H
# define MINISHELL_H


/* ******************* */
/*      LIBRARIES      */
/* ******************* */

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

/* ******************* */
/*       MACROS        */
/* ******************* */

/* terminal colors */
# define RED "\033[0;31m"
# define GRE "\033[0;32m"
# define YEL "\033[0;33m"
# define BLU "\033[0;34m"
# define MAG "\033[0;35m"
# define CYA "\033[0;36m"
# define WHI "\033[0m"

/* error status code */
# define BUILTIN_FAILURE 2

/* ******************* */
/*        FILES        */
/* ******************* */

/* PROMPT.C*/
int		print_prompt(void);

/* BUILTINS.C*/
int		pwd(char *cmd);
int		cd(char *cmd);
int		echo(char *cmd);
int		ls(char *cmd, char **env);				// provisoire
void	execute_cmd(char *cmd, char **env);

#endif
