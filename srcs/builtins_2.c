/* Adrien's builtins */

#include "../includes/minishell.h"

/* info sur les exit-status (pdf p.15)
All of the Bash builtins return an exit status of zero if they succeed 
and a non-zero status on failure, 
so they may be used by the conditional and list constructs. 
All builtins return an exit status of 2 to indicate incorrect usage, 
generally invalid options or missing arguments.

-> j'ai défini une macro dans minishell.h pour les builtin errors: 
exit(BUILTIN_FAILURE)
*/