/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 00:56:18 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	_jungyeok(t_command **command, char **envp)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (!command[i]->program[0])
			_err("bash: syntax error near unexpected token `|'");
		i++;
	}
	envp = NULL;
	command = NULL;
}
