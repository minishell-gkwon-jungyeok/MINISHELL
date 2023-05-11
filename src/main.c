/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/11 11:34:22 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_cmd_info(t_command **cmd, t_mini *c, int i)
{
	while (++i < c->cmd_cnt)
	{
		if ((*cmd)[i].info[0])
			(*cmd)[i].input = ft_strdup((*cmd)[i].info[0]);
		if ((*cmd)[i].info[1])
			(*cmd)[i].output = ft_strdup((*cmd)[i].info[1]);
		if ((*cmd)[i].info[2])
			(*cmd)[i].delimiter = ft_strdup((*cmd)[i].info[2]);
		if ((*cmd)[i].info[3])
			(*cmd)[i].output_append = ft_strdup((*cmd)[i].info[3]);
	}
}

void	del_quotes(t_command **cmd, t_mini *c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < c->cmd_cnt)
	{
		j = -1;
		while (cmd[i]->cmd[++j])
			cmd[i]->cmd[j] = ft_realloc_c(cmd[i]->cmd[j], 7);
		j = -1;
		while (++j < 4)
			if (cmd[i]->info[j])
				cmd[i]->info[j] = ft_realloc_c(cmd[i]->info[j], 7);
	}
}

int	tokenize(char *line, t_command **cmd, t_mini *c)
{
	char	**nodes;
	int		i;

	nodes = ft_split(line, '|');
	if (!nodes[0] || !is_ended_quote(nodes, -1, 0))
	{
		free(nodes);
		return (1);
	}
	doller_parse_with_del_quot(&nodes, c);
	i = -1;
	while (++i < c->cmd_cnt)
		init_cmd(nodes[i], *cmd + i);
	del_quotes(cmd, c);
	builtin_check(*cmd, c->cmd_cnt);
	init_cmd_info(cmd, c, -1);
	free(nodes);
	return (0);
}

void	display(t_mini *c)
{
	t_command	*cmd;
	char		*line;

	line = NULL;
	while (1)
	{
		line = readline("jungkwon$ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			if (pipe_split(&line, &cmd, c))
				continue ;
//			dprintf(2, "After pipe_split\n");
//			for (int i = 0; cmd[i].unit; i++)
//				dprintf(2, "cmd[%d].unit = %s\n", i, cmd[i].unit);
			c->cmd_cnt = c->ncmd;
			env_change(&cmd, c->env, c->ncmd);
//			dprintf(2, "After env_change\n");
//			for (int i = 0; cmd[i].unit; i++)
//				dprintf(2, "cmd[%d].unit = %s\n", i, cmd[i].unit);
			bracket_remove(&cmd, c->ncmd);
//			dprintf(2, "After bracket_remove\n");
//			for (int i = 0; cmd[i].unit; i++)
//				dprintf(2, "cmd[%d].unit = %s\n", i, cmd[i].unit);
			_32split(&cmd, c->ncmd);
//			dprintf(2, "After _32split\n");
//			for (int i = 0; cmd[i].cmd; i++){
//				for (int j = 0; cmd[i].cmd[j]; j++)
//					dprintf(2, "cmd[%d].cmd[%d] = %s\n", i, j, cmd[i].cmd[j]);
//			}
			_3439to7(&cmd, c->ncmd);
//			dprintf(2, "After _3439to7\n");
//			for (int i = 0; cmd[i].cmd; i++){
//				for (int j = 0; cmd[i].cmd[j]; j++)
//					dprintf(2, "cmd[%d].cmd[%d] = %s\n", i, j, cmd[i].cmd[j]);
//			}
			is_builtin(&cmd, c->ncmd);
/*
			dprintf(2, "After is_builtin\n");
			for (int i = 0; cmd[i].cmd; i++){
				dprintf(2, "built_in = %d\n", cmd[i].built_in);
				for (int j = 0; cmd[i].cmd[j]; j++){
					dprintf(2, "cmd[%d].cmd[%d] = %s\n", i, j, cmd[i].cmd[j]);
					dprintf(2, "len = %d\n", ft_strlen(cmd[i].cmd[j]));
					for (int k=0;cmd[i].cmd[j][k];k++)
						dprintf(2, "k = %d\n", (int)cmd[i].cmd[j][k]);
				}
				if (cmd[i].input)
					dprintf(2, "cmd[%d].input = %s\n", i, cmd[i].input);
				if (cmd[i].delimiter)
					dprintf(2, "cmd[%d].delimiter = %s\n", i, cmd[i].delimiter);
				if (cmd[i].output)
					dprintf(2, "cmd[%d].output = %s\n", i, cmd[i].output);
				if (cmd[i].output_append)
					dprintf(2, "cmd[%d].output_append = %s\n", i, cmd[i].output_append);
			}
*/
			_jungyeok(cmd, c, c->ncmd - 1);
/*
			if (!is_ended_quote(&line, -1, 0))
				ft_err("invalid quotes");
			c->cmd_cnt = pipe_cnt(line) + 1;
			cmd = ft_calloc(sizeof(t_command), c->cmd_cnt);
			if (tokenize(line, &cmd, c))
			{
				ft_free_command(&cmd, c);
				continue ;
			}
			if (!cmd->cmd[0] && cmd->info[2][0])
				_heredoc(cmd->info[2], c);
			else
				_jungyeok(cmd, c, c->cmd_cnt - 1);
*/
			ft_free_command(&cmd, c);
			system("leaks minishell");
		}
	}
}

void	main_init(int argc)
{
	struct termios	term;

	if (argc != 1)
		exit(1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal_handlers();
}

int	main(int ac, char **av, char **env)
{
	t_mini			c;
	struct termios	term;

	(void)av;
	tcgetattr(STDIN_FILENO, &term);
	main_init(ac);
	ft_memset(&c, 0, sizeof(t_mini));
	c.index = 0;
	while (env[c.index])
		c.index++;
	c.env = ft_calloc(8, c.index + 1);
	c.index = -1;
	while (env[++c.index])
		c.env[c.index] = ft_strdup(env[c.index]);
	display(&c);
	c.index = -1;
	while (c.env[++c.index])
		free(c.env[c.index]);
	free(c.env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
