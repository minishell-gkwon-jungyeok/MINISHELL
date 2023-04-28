/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:13:15 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 01:54:11 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_access(char **path, t_command *cmd, t_mini *c)
{
	char	*d;
	char	*ret;

	while (*path)
	{
		d = ft_strjoin(*path, "/");
		ret = ft_strjoin(d, cmd->program[0]);
		free(d);
		if (!access(ret, 0))
		{
			c->cmd = ret;
			return ;
		}
		free(ret);
		path++;
	}
}

void	_c_cmd(t_command *command, t_mini *c)
{
	if (!command[c->index].built_in)
		command_access(c->path, &command[c->index], c);
	else if (command[c->index].built_in)
		c->cmd = ft_strdup(command[c->index].program[0]);
}

void    exe_builtin2(char *s, t_command *command, t_mini *c)
{
	if (!ft_strcmp(s, "echo"))
		_echo(command + c->index);
	else if (!ft_strcmp(s, "cd"))
		_cd(command + c->index);
	else if (!ft_strcmp(s, "exit"))
		__exit(command + c->index);
}

void	exe_builtin1(char *s, t_command *command, t_mini *c)
{
	if (!ft_strcmp(s, "pwd"))
		_pwd();
	else if (!ft_strcmp(s, "env"))
		_env(c->env);
	else if (!ft_strcmp(s, "export"))
		_export(command + c->index, &c->env);
	else if (!ft_strcmp(s, "unset"))
		_unset(command + c->index, &c->env);
	else
		exe_builtin2(s, command, c);
}

void	_exe(t_command *command, t_mini *c)
{
	if (command->built_in)
		exe_builtin1(command[c->index].program[0], command, c);
	else
		execve(c->cmd, command[c->index].program, c->env);
}
