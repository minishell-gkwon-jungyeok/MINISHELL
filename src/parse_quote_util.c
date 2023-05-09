/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:30:28 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/09 17:46:01 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	doller_parse_with_del_quot(char ***nodes, t_sys_info *info, char **env)
{
	int	i;

	i = -1;
	while (++i < info->cmd_cnt)
		parse(&(*nodes)[i], env);
	return (1);
}
