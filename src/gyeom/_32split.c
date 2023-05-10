/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _32split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 01:31:54 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/10 01:35:44 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_32split(t_command **cmd, int ncmd)
{
	int	i;

	i = -1;
	while (++i < ncmd)
	{
		(*cmd)[i].cmd = split_jungyeok((*cmd)[i].unit, 32);
		ft_memset((*cmd)[i].unit, 0, ft_strlen((*cmd)[i].unit));
		free((*cmd)[i].unit);
	}
}
