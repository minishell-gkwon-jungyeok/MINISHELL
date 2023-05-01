/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:49:10 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/02 00:00:08 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	total_len(char const *str, char c)
{
	int	i;
	int	count;
	char quote;
	int was_in;

	was_in = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == '\"' || str[i] == '\'')
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

	i = 0;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static int	word_count(char const *str, char c)
{
	int	len;
	char quote;

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
	t_len = total_len(s, c);
	ret = (char **)malloc(sizeof(char *) * (t_len + 1));
	if (!ret)
		return (0);
	ret[t_len] = 0;
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
