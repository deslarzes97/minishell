/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:43:04 by tnanchen          #+#    #+#             */
/*   Updated: 2022/01/16 21:15:15 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	permission_error_msg(char *msg, char *file)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(file, 2);
	ft_putchar_fd('\n', 2);
}

int	get_files_fd(char *infile, char *outfile, int *infile_fd, int *outfile_fd)
{
	if (access(infile, R_OK) == -1)			// test reading permission
	{
		permission_error_msg(strerror(errno), infile);
		exit(PERMISSION_ERROR);
	}
	if (access(outfile, F_OK) == 0)			// test existence (if doesn't exists, no need to test permission cause the prog will create it)
	{
		if (access(outfile, W_OK) == -1)	// test writing permission
		{
			permission_error_msg(strerror(errno), outfile);
			exit(PERMISSION_ERROR);
		}
	}
	*infile_fd = open(infile, O_RDONLY);
	if (*infile_fd == -1)
		exit(UNPREDICTABLE_ERROR);
	*outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (*outfile_fd == -1)
		exit(UNPREDICTABLE_ERROR);
	return (0);
}
