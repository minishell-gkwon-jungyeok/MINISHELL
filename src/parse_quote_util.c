/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:30:28 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/09 07:33:38 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	doller_parse_with_del_quot(t_command *cmd, t_sys_info *info, char **env)
{
	int	i;
	int	j;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while (cmd[i].cmd[++j])
			parse(&cmd[i].cmd[j], env);
		j = -1;
		while (++j < 4)
			if (cmd[i].info[j])
				parse(&cmd[i].info[j], env);
	}
	return (1);
}
