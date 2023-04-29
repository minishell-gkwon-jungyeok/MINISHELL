/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 22:00:36 by edwin             #+#    #+#             */
/*   Updated: 2023/04/29 22:00:48 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_set_quotes(char line, int quotes)
{
	int	result;

	result = quotes;
	if (line == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (line == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

int	ft_line_quote(char *line)
{
	int at;
	int	quotes;

	at = 0;
	quotes = 0;
	while (line[at])
	{
		quotes = parse_set_quotes(line[at], quotes);
		at++;
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
	{
		printf("test exit: quotes error\n");
		exit(1);
	}
	return (0);
}