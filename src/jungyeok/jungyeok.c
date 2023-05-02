/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/03 03:02:54 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_path(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

int	_run(t_command *command, t_mini *c)
{
	if (!c->pid)
	{
		fclose_pipe(c, c->index, c->ncmd - 1);
		if (open_fd(command, c))
			exit(1);
		_c_cmd(command, c);
		close_pipe(c, c->ncmd - 1);
		close_fd(command, c);
		_exe(command, c);
		free(c->cmd);
		exit(0);
	}
	return (0);
}

int	_run_cmd(t_command *command, int ncmd, t_mini *c, char **envp)
{
	int	wait;

	c->index = 0;
	while (envp[c->index])
		c->index++;
	c->env = ft_calloc(8, c->index + 1);
	c->index = -1;
	while (envp[++c->index])
		c->env[c->index] = ft_strdup(envp[c->index]);
	c->index = -1;
	while (++c->index < ncmd)
	{
		c->pid = fork();
		if (c->pid == 0)
			_run(command, c);
	}
	if (c->pipe)
	{
		close_pipe(c, c->ncmd - 1);
		close_fd(command, c);
	}
	wait = 1;
	while (wait > 0)
		wait = waitpid(-1, NULL, 0);
	return (0);
}

void	free_jungyeok(t_mini *c)
{
	c->index = -1;
	while (c->path[++c->index])
		free(c->path[c->index]);
	free(c->path);
	c->index = -1;
	while (c->env[++c->index])
		free(c->env[c->index]);
	free(c->env);
	free(c->pipe);
}

int	_jungyeok(t_command *command, char **envp, int npipe)
{
	char	*pat;
	t_mini	c;

	ft_memset(&c, 0, sizeof(t_mini));
	c.ncmd = npipe + 1;
	if (c.ncmd > 20)
		return (_err("no more than 20 pipes"));
	pat = find_path(envp);
	c.path = ft_split(pat, ':');
	if (open_pipe(&c, npipe))
		return (1);
	if (_run_cmd(command, c.ncmd, &c, envp))
		return (1);
	free_jungyeok(&c);
	return (0);
}
