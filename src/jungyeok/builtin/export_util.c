/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:05:57 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:51:18 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	check61(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] == 61)
				return (true);
			i++;
		}
	}
	return (false);
}

void	__dp(char *s, char ***env)
{
	int		len;
	int		i;
	char	*tmp;

	tmp = ft_strdup_c(s, 61);
	len = ft_strlen(tmp);
	i = -1;
	while ((*env)[++i])
		if (ft_strncmp((*env)[i], tmp, len))
			break ;
	ft_memset(tmp, 0, len);
	free(tmp);
	tmp = (*env)[i];
	ft_memset(tmp, 0, len);
	free(tmp);
	(*env)[i] = ft_strdup(s);
}

bool	check_env(char *s, char ***env)
{
	int		ret;
	int		i;
	int		len;
	char	*tmp;

	tmp = ft_strdup_c(s, 61);
	len = ft_strlen(tmp);
	i = -1;
	ret = 1;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], tmp, len))
			ret = 0;
	}
	ft_memset(tmp, 0, len);
	free(tmp);
	if (ret)
		return (true);
	if (check61(s))
		__dp(s, env);
	return (false);
}

void	_write(char *s)
{
	int	i;

	i = 0;
	if (!check61(s))
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
		return ;
	}
	while (s[i] != 61)
		write(1, s + i++, 1);
	write(1, s + i++, 1);
	write(1, "\"", 1);
	while (s[i])
		write(1, s + i++, 1);
	write(1, "\"\n", 2);
}
