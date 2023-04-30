/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:49:10 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/30 18:59:08 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static int	total_len(char const *str, char c)
//{
//	int	i;
//	int	count;

//	count = 0;
//	i = 0;
//	while (str[i])
//	{
//		if (str[i] == '\"')
//			while (str[i] != '\"')
//				i++;
//		if (str[i] == '\'')
//			while (str[i] != '\'')
//				i++;
//		while (str[i] && str[i] == c)
//			i++;
//		if (str[i])
//			count++;
//		if (str[i] == '\"')
//			while (str[i] != '\"')
//				i++;
//		if (str[i] == '\'')
//			while (str[i] != '\'')
//				i++;
//		while (str[i] && str[i] != c)
//			i++;
//	}
//	return (count);
//}

//static char	*get_word(char const *str, int len)
//{
//	char	*ret;
//	int		i;

//	i = 0;
//	ret = (char *)malloc(sizeof(char) * (len + 1));
//	if (!ret)
//		return (NULL);
//	while (i < len)
//	{
//		ret[i] = str[i];
//		i++;
//	}
//	ret[i] = 0;
//	return (ret);
//}

//static int	word_count(char const *str, char c)
//{
//	int	len;

//	len = 0;
//	while (str[len] != c && str[len])
//		len++;
//	return (len);
//}

//static char	**ft_split_free(char **ret, int i)
//{
//	while (i)
//		free(ret[--i]);
//	free(ret);
//	return (0);
//}

//char	**ft_split(char const *s, char c)
//{
//	int		t_len;
//	char	**ret;
//	int		i;
//	int		count;

//	i = 0;
//	t_len = total_len(s, c);
//	ret = (char **)malloc(sizeof(char *) * (t_len + 1));
//	if (!ret)
//		return (0);
//	ret[t_len] = 0;
//	while (*s && i < t_len)
//	{
//		while (*s && *s == c)
//			s++;
//		if (*s)
//		{
//			//if (*s == '\"')
//			//	while (*s != '\"')
//			//		s++;
//			//if (*s == '\'')
//			//	while (*s != '\'')
//			//		i++;
//			count = word_count(s, c);
//			ret[i] = get_word(s, count);
//			if (!ret[i++])
//				return (ft_split_free(ret, i));
//			s += count;
//		}
//	}
//	return (ret);
//}

#include "../includes/minishell.h"

static int	is_delim(char a, char c, char quote)
{
	return (a == c && quote == 0);
}

static int	total_len(char const *str, char c)
{
	int		i;
	int		count;
	char	quote;

	count = 0;
	i = 0;
	quote = 0;
	while (str[i])
	{
		while (str[i] && is_delim(str[i], c, quote))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && (is_delim(str[i], c, quote) == 0))
			{
				if (str[i] == '"' || str[i] == '\'')
					quote = (quote == str[i]) ? 0 : str[i];
				i++;
			}
		}
	}
	return (count);
}

static int	word_count(char const *str, char c)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (str[len] && !(is_delim(str[len], c, quote)))
	{
		if (str[len] == '"' || str[len] == '\'')
			quote = (quote == str[len]) ? 0 : str[len];
		len++;
	}
	return (len);
}

static char	*get_word(char const *str, int len)
{
	char	*ret;
	int		i;
	int		j;
	char	quote;

	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (i < len)
	{
		if (str[i] == '"' || str[i] == '\'')
			quote = (quote == str[i]) ? 0 : str[i];
		else
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	ret[j] = 0;
	return (ret);
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
		while (*s && is_delim(*s, c, 0))
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

