/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:47:54 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/17 13:45:48 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>

# include "libft/libft.h"

# define UNPREDICTABLE_ERROR 1
# define PERMISSION_ERROR 126
# define EXEC_ERROR 127

# define HERE_DOC 1

typedef struct s_file
{
	char	*filename;
	int		fd;
}	t_file;

int		check_here_doc_param(int ac, char **av, t_file *infile, t_file *outfile);
void	get_files_fd(int files_mode, t_file *infile, t_file *outfile);
void	execute_cmd(char *cmd, char **envp);

#endif
