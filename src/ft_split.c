/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:54:10 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/10 02:09:07 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	total_len(char const *str, char c, int i, int count)
{
	char	quote;
	int		was_in;

	was_in = 0;
	while (str[i])
	{
		while (str[i] == 34 || str[i] == 39)
		{
			was_in = 1;
			quote = str[i++];
			while (str[i] != quote)
				i++;
			i++;
		}
		if (was_in)
			count++;
		while (str[i] && str[i] == c)
			i++;
		if (c == ' ' && (str[i] == 34 || str[i] == 39))
			continue ;
		if (str[i])
			count++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (count);
}

static char	*get_word(char const *str, int len)
{
	char	*ret;
	int		i;

	ret = ft_calloc(1, len + 1);
	i = -1;
	while (++i < len)
		ret[i] = str[i];
	return (ret);
}

static int	word_count(char const *str, char c)
{
	int		len;
	char	quote;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\"' || str[len] == '\'')
		{
			quote = str[len++];
			while (str[len] != quote)
				len++;
		}
		if (str[len] != c)
			len++;
		else
			break ;
	}
	return (len);
}

static char	**ft_split_free(char **ret, int i)
{
	while (i)
		free(ret[--i]);
	free(ret);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		t_len;
	char	**ret;
	int		i;
	int		count;

	i = 0;
	t_len = total_len(s, c, i, i);
	ret = ft_calloc(8, t_len + 1);
	while (*s && i < t_len)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			count = word_count(s, c);
			ret[i] = get_word(s, count);
			if (!ret[i++])
				return (ft_split_free(ret, i));
			s += count;
		}
	}
	return (ret);
}
