/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:22:05 by desa              #+#    #+#             */
/*   Updated: 2022/01/28 15:51:01 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo(char *cmd)
{
	char	**split_args;
	char	*temp;

	split_args = ft_split_blank(cmd);
	if (split_args[1] == NULL)
		ft_putstr_fd("\n", 1);
	else if (ft_strncmp(split_args[1], "-n", 2))
		ft_putstr_fd(split_args[2], 1);
	else
		ft_putendl_fd(split_args[1], 1);
	return (0);
}
