/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bracket_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:57:10 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 15:36:42 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_delim(t_command **cmd, int i, char *s, int cur)
{
	int	index;
	int	jndex;
	int	len;

	index = cur;
	while (s[index] == 60 || s[index] == 32)
		s[index++] = 32;
	len = 0;
	(*cmd)[i].delimiter = ft_strdup3439(s + index, &len);
	jndex = -1;
	while (++jndex < len)
		s[index + jndex] = 32;
}

void	_in(t_command **cmd, int i, char *s, int cur)
{
	int	index;
	int	jndex;
	int	len;

	index = cur;
	while (s[index] == 60 || s[index] == 32)
		s[index++] = 32;
	len = 0;
	(*cmd)[i].input = ft_strdup3439(s + index, &len);
	jndex = -1;
	while (++jndex < len)
		s[index + jndex] = 32;
}

void	_out(t_command **cmd, int i, char *s, int cur)
{
	int	index;
	int	jndex;
	int	len;

	index = cur;
	while (s[index] == 62 || s[index] == 32)
		s[index++] = 32;
	len = 0;
	(*cmd)[i].output = ft_strdup3439(s + index, &len);
	jndex = -1;
	while (++jndex < len)
		s[index + jndex] = 32;
}

void	_out_a(t_command **cmd, int i, char *s, int cur)
{
	int	index;
	int	jndex;
	int	len;

	index = cur;
	while (s[index] == 62 || s[index] == 32)
		s[index++] = 32;
	len = 0;
	(*cmd)[i].output_append = ft_strdup3439(s + index, &len);
	jndex = -1;
	while (++jndex < len)
		s[index + jndex] = 32;
}

void	bracket_remove(t_command **cmd, int ncmd)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ncmd)
	{
		j = 0;
		while ((*cmd)[i].unit[j])
		{
			if (!if_in34((*cmd)[i].unit, j)
				&& !if_in39((*cmd)[i].unit, j))
			{
				if ((*cmd)[i].unit[j] == 60 && (*cmd)[i].unit[j + 1] == 60)
					_delim(cmd, i, (*cmd)[i].unit, j);
				else if ((*cmd)[i].unit[j] == 60)
					_in(cmd, i, (*cmd)[i].unit, j);
				else if ((*cmd)[i].unit[j] == 62 && (*cmd)[i].unit[j + 1] == 62)
					_out_a(cmd, i, (*cmd)[i].unit, j);
				else if ((*cmd)[i].unit[j] == 62)
					_out(cmd, i, (*cmd)[i].unit, j);
			}
			j++;
		}
	}
}
