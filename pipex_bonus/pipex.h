/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:47:54 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/16 21:04:22 by tnanchen         ###   ########.fr       */
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

int		get_files_fd(char *infile, char *outfile, int *infile_fd, int *outfile_fd);
char	*find_path(char *cmd, char **envp);

#endif
