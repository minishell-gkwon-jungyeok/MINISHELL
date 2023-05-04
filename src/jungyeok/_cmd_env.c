/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cmd_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:38:40 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/04 23:07:23 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_env_(char **s, int c)
{
	char	*tmp;

	tmp = (*s);
	free(tmp);
	*s = ft_itoa(c);
}

void	cmd_env__(char **s, char **env)
{
	int		i;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], (*s) + 1, ft_strlen((*s) + 1)))
		{
			tmp = (*s);
			free(tmp);
			tmp = ft_strchr(env[i], (int) '=');
			tmp++;
			(*s) = ft_strdup(tmp);
		}
	}
}

void	_cmd_env(t_command *command, char **env, t_mini *c)
{
	int		i;
	int		j;

	i = -1;
	while (++i < c->ncmd)
	{
		j = -1;
		while (command[i].program[++j])
		{
			if (!ft_strncmp(command[i].program[j], "$?", 3))
				cmd_env_(command[i].program + j, c->dollar);
			else if (command[i].program[j][0] == '$')
				cmd_env__(command[i].program + j, env);
		}
	}
}
