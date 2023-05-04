/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:33:38 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/03 12:56:53 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_pipe(t_mini *c, int opened)
{
	int	i;
	int	j;

	i = 0;
	j = opened << 1;
	while (i < j)
	{
		close(c->pipe[i]);
		i++;
	}
	return (1);
}

int	open_pipe(t_mini *c, int npipe)
{
	int	i;

	c->pipe = ft_calloc(4, 2 * npipe + 1);
	i = 0;
	while (i < npipe)
	{
		if (pipe(c->pipe + (i << 1)) < 0)
			return (close_pipe(c, i - 2));
		i++;
	}
	return (0);
}
