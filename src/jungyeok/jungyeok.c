/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/09 00:26:57 by jungyeok         ###   ########.fr       */
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
}

int	_run_cmd(t_command *command, int ncmd, t_mini *c)
{
	int	wait;

	c->index = -1;
	while (++c->index < ncmd)
	{
		if (!ft_strncmp(command[c->index].cmd[0], "export", 7) ||
			!ft_strncmp(command[c->index].cmd[0], "exit", 5) ||
			!ft_strncmp(command[c->index].cmd[0], "cd", 3) ||
			!ft_strncmp(command[c->index].cmd[0], "unset", 6))
		{
			fclose_pipe(c, c->index, c->ncmd - 1);
			open_fd(command, c);
			exe_builtin(command[c->index].cmd[0], command, c);
			close_pipe(c, c->ncmd - 1);
			close_fd(command, c);
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

void    _(t_command *cmd, int npipe) {
	for (int i = 0; i <= npipe; i++){
		for (int j = 0; cmd[i].cmd[j]; j++)
			dprintf(2, "cmd[%d].cmd[%d] : %s\n", i, j, cmd[i].cmd[j]);
		dprintf(2, "bul : %d\n", cmd[i].built_in);
		dprintf(2, "inp is : %s\n", cmd[i].input);
		dprintf(2, "oup is : %s\n", cmd[i].output);
		dprintf(2, "del is : %s\n", cmd[i].delimiter);
		dprintf(2, "oap is : %s\n", cmd[i].output_append);
	}
}

int	_jungyeok(t_command *command, t_mini *c, int npipe)
{
	char	*pat;

//	_(command, npipe);
	c->ncmd = npipe + 1; 
	if (c->ncmd > 20)
		return (_err("no more than 20 pipes"));
	_cmd_env(command, c->env, c);
	pat = find_path(c->env);
	c->path = ft_split(pat, ':');
	if (open_pipe(c, npipe))
		return (1);
	if (_run_cmd(command, c->ncmd, c))
		return (1);
	free_jungyeok(c);
	return (0);
}
