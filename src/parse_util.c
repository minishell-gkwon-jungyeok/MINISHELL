/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:57:52 by edwin             #+#    #+#             */
/*   Updated: 2023/05/03 04:48:29 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_cnt(char *line)
{
	int		cnt;
	char	quote;

	cnt = 0;
	while (*line)
	{
		while (*line == '\"' || *line == '\'')
		{
			quote = *line;
			line++;
			while (*line != quote)
				line++;
			line++;
		}
		if (*line == '|')
			cnt++;
		if (!*line)
			break ;
		line++;
	}
	return (cnt);
}
