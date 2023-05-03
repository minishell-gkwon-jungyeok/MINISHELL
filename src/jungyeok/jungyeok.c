/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/03 13:39:46 by jungyeok         ###   ########.fr       */
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
	fclose_pipe(c, c->index, c->ncmd - 1);
	if (open_fd(command, c))
		exit(1);
	_c_cmd(command, c);
	close_pipe(c, c->ncmd - 1);
	close_fd(command, c);
	_exe(command, c);
	free(c->cmd);
	exit(0);
	return (0);
}

int	_run_cmd(t_command *command, int ncmd, t_mini *c)
{
	int	wait;

	c->index = -1;
	while (++c->index < ncmd)
	{
		if (command[c->index].built_in)
		{
			exe_builtin(command[c->index].program[0], command, c);
			continue ;
		}
		c->pid = fork();
		if (!c->pid)
			_run(command, c);
	}
	if (c->pipe)
		close_pipe(c, c->ncmd - 1);
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
	free(c->pipe);
}

int	_jungyeok(t_command *command, t_mini *c, int npipe)
{
	char	*pat;

	c->ncmd = npipe + 1;
	if (c->ncmd > 20)
		return (_err("no more than 20 pipes"));
//	_cmd_env(command, c->env, c);	$USER >> jungyeok 바꾸고, $? >> c->collar 바꾸기
	pat = find_path(c->env);
	c->path = ft_split(pat, ':');
	if (open_pipe(c, npipe))
		return (1);
	if (_run_cmd(command, c->ncmd, c))
		return (1);
	free_jungyeok(c);
	return (0);
}
