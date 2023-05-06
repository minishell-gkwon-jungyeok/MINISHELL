/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:13:15 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/05 21:42:20 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_access(char **path, t_command *cmd, t_mini *c)
{
	char	*d;
	char	*ret;

	if (!access(cmd->cmd[0], 0))
	{
		c->cmd = ft_strdup(cmd->cmd[0]);
		return ;
	}
	while (*path)
	{
		d = strjoin_jungyeok(*path, "/");
		ret = strjoin_jungyeok(d, cmd->cmd[0]);
		free(d);
		if (!access(ret, 0))
		{
			c->cmd = ret;
			return ;
		}
		free(ret);
		path++;
	}
	write(2, "bash: ", 6);
	write(2, cmd[c->index].cmd[0], ft_strlen(cmd[c->index].cmd[0]));
	write(2, ": command not found\n", 20);
}

void	_c_cmd(t_command *command, t_mini *c)
{
	if (!command[c->index].built_in)
		command_access(c->path, &command[c->index], c);
	else if (command[c->index].built_in)
		c->cmd = ft_strdup(command[c->index].cmd[0]);
}

void	exe_builtin(char *s, t_command *command, t_mini *c)
{
	if (!ft_strcmp(s, "pwd"))
		_pwd();
	else if (!ft_strcmp(s, "env"))
		_env(c->env);
	else if (!ft_strcmp(s, "export"))
		_export(command + c->index, &c->env);
	else if (!ft_strcmp(s, "unset"))
		_unset(command + c->index, &c->env);
	else if (!ft_strcmp(s, "echo"))
		_echo(command + c->index, c);
	else if (!ft_strcmp(s, "cd"))
		_cd(command + c->index);
	else if (!ft_strcmp(s, "exit"))
		__exit(command + c->index, c);
}

void	_exe(t_command *command, t_mini *c)
{
	if (command[c->index].built_in)
	{
		exe_builtin(command[c->index].cmd[0], command, c);
		exit(0);
	}
	else
	{
		if (execve(c->cmd, command[c->index].cmd, c->env) < 0)
			exit(1);
		exit(0);
	}
}
