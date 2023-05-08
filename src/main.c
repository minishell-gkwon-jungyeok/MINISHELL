/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/09 07:27:59 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 14dd
 *
void	_print(t_command **cmd, t_sys_info *info) {
	for (int i = 0; i < info->cmd_cnt; i++){
		for (int j = 0; (*cmd + i)->cmd[j]; j++)
			printf("cmd[%d].cmd[%d] is : %s\n", i, j, (*cmd + i)->cmd[j]);
		printf("builtin is : %d\n", (*cmd + i)->built_in);
		printf("input is : %s\n", (*cmd + i)->info[0]);
		printf("output is : %s\n", (*cmd + i)->info[1]);
		printf("del is : %s\n", (*cmd + i)->info[2]);
		printf("output_append is : %s\n", (*cmd + i)->info[3]);
	}
}
*/

void	init_cmd_info(t_command **cmd, t_sys_info *info)
{
	int	i;

	i = -1;
	while (++i < info->cmd_cnt)
	{
		if ((*cmd)[i].info[0])
			(*cmd)[i].input = (*cmd)[i].info[0];
		if ((*cmd)[i].info[1])
			(*cmd)[i].output = (*cmd)[i].info[1];
		if ((*cmd)[i].info[2])
			(*cmd)[i].delimiter = (*cmd)[i].info[2];
		if ((*cmd)[i].info[3])
			(*cmd)[i].output_append = (*cmd)[i].info[3];
	}
}

int	tokenize(char *line, t_command **cmd, t_sys_info *info, char **env)
{
	char	**nodes;
	int		i;

	nodes = ft_split(line, '|');
	if (!nodes[0] || !is_ended_quote(nodes, -1, 0))
	{
		free(nodes);
		return (1);
	}
	i = -1;
	while (++i < info->cmd_cnt)
		init_cmd(nodes[i], *cmd + i);
	doller_parse_with_del_quot(*cmd, info, env);
	builtin_check(*cmd, info->cmd_cnt);
	init_cmd_info(cmd, info);
//	_print(cmd, info);
	free(nodes);
	return (0);
}

void	display(t_sys_info *info, t_mini *c, char **env)
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
			if (!is_ended_quote(&line, -1, 0))
				ft_err("invalid quotes");
			info->cmd_cnt = pipe_cnt(line) + 1;
			cmd = ft_calloc(sizeof(t_command), info->cmd_cnt);
			if (tokenize(line, &cmd, info, env))
			{
				ft_free_command(&cmd, info);
				continue ;
			}
			_jungyeok(cmd, c, info->cmd_cnt - 1);
			ft_free_command(&cmd, info);
		}
	}
}

void	main_init(int argc, char *argv[])
{
	struct termios	term;

	if (argc != 1)
		exit(1);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	set_signal_handlers();
	(void)argc;
	(void)argv;
}

int	main(int ac, char **av, char **env)
{
	t_sys_info		info;
	t_mini			c;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(ac, av);
	ft_memset(&c, 0, sizeof(t_mini));
	c.index = 0;
	while (env[c.index])
		c.index++;
	c.env = ft_calloc(8, c.index + 1);
	c.index = -1;
	while (env[++c.index])
		c.env[c.index] = ft_strdup(env[c.index]);
	display(&info, &c, env);
	(void)av;
	c.index = -1;
	while (c.env[++c.index])
		free(c.env[c.index]);
	free(c.env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
