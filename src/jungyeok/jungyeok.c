/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 22:57:18 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/27 15:44:56 by jungyeok         ###   ########.fr       */
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
	c->pid = fork();
	if (!c->pid)
	{
/*		if (c->index == 0)
			_dup2(command, c, c->fd_in, c->pipe[1]);
		else if (c->index == c->ncmd - 1)
			_dup2(command, c, c->pipe[2 * c->index - 2], c->fd_out);
		else
			_dup2(command, c, c->pipe[2 * c->index - 2]
				, c->pipe[2 * c->index + 1]);
		close_pipe(c, c->ncmd - 1);
*/		if (!command[c->index].built_in)
			command_access(c->path, &command[c->index], c);
		else if (command[c->index].built_in)
			c->cmd = ft_strdup(command[c->index].program[0]);
		printf("c->cmd = %s\n", c->cmd);
/*		if (command->built_in)
			builtin(c->cmd, command[c->index]->program, c->env);
		else
			execve(c->cmd, command[c->index]->program, c->env);
*/		free(c->cmd);
		exit(1);
	}
	return (0);
}


int	_run_cmd(t_command *command, int ncmd, t_mini *c, char **envp)
{
	c->index = -1;
	while (envp[++c->index]);
	c->env = ft_calloc(8, c->index + 1);
	c->index = -1;
	while (envp[++c->index])
		c->env[c->index] = ft_strdup(envp[c->index]);
	c->index = -1;
	while (++(c->index) < ncmd)
		if (_run(command, c))
			return (1);
	waitpid(-1, NULL, 0);
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
	if (c.ncmd > 200)
		return (_err("no more than 200 pipes"));
	pat = find_path(envp);
	c.path = ft_split(pat, ':');
	if (open_pipe(&c, npipe))
		return (1);
	if (_run_cmd(command, c.ncmd, &c, envp))
		return (1);
	close_pipe(&c, npipe);
	free_jungyeok(&c);
	return (0);
}
