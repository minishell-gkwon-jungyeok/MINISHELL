/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 22:39:56 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int	_run(t_command **command, t_mini *c, char **envp)
{
	c->pid = fork();
	if (!c->pid)
	{
		if (c->index == 0)
			_dup(command, c, c->fd_in, c->pipe[1]);
		else if (c->index == c->ncmd - 1)
			_dup(command, c, c->pipe[2 * c->index - 2], c->fd_out);
		else
			_dup(command, c, c->pipe[2 * c->index - 2]
				, c->pipe[2 * c->index + 1]);
		close_pipe(c, c->ncmd - 1);
		if (command_access(c->path, command[c->index], c))
			return (1);
		execve(c->cmd, command[c->index]->program, envp);
	}
	return (0);
}

int	_run_cmd(t_command **command, int ncmd, t_mini *c, char **envp)
{
	c->index = -1;
	while (++c->index < ncmd)
		if (_run(command, c, envp))
			return (1);
	waitpid(-1, NULL, 0);
	return (0);
}

int	_jungyeok(t_command **command, char **envp)
{
	char	*pat;
	t_mini	c;

	ft_memset(&c, 0, sizeof(t_mini));
	c.ncmd = -1;
	while (command[++c.ncmd])
	{
		if (!command[c.ncmd]->program[0])
			return (_err("bash: syntax error near unexpected token `|'"));
	}
	if (c.ncmd > 200)
		return (_err("no more than 200 pipes"));
	pat = find_path(envp);
	ft_memset(&c, 0, sizeof(t_mini));
	c.path = ft_split(pat, ':');
	if (open_pipe(&c, c.ncmd - 1))
		return (1);
	if (_run_cmd(command, c.ncmd, &c, envp))
		return (1);
	close_pipe(&c, c.ncmd - 1);
	c.ncmd = -1;
	while (c.path[++c.ncmd])
		free(c.path[c.ncmd]);
	free(c.path);
	return (0);
}
