/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/03 19:25:07 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenize(char *line, t_command **cmd, t_sys_info *info)
{
	char	**nodes;
	int		i;
	int		j;

	nodes = ft_split(line, '|');
	if (!is_ended_quote(nodes))
		exit(1);
	if (!nodes[0])
	{
		free(nodes);
		return (0);
	}
	i = -1;
	while (++i < info->cmd_cnt)
		init_cmd(nodes[i], *cmd + i);
	doller_parse_with_del_quot(*cmd, info);
	builtin_check(*cmd, info);
	j = 0;
	// i = -1;
	// while (++i < info->cmd_cnt)
	// {
	// 	j = -1;
	// 	while ((*cmd + i)->program[++j])
	// 		printf("program is : %s\n", (*cmd + i)->program[j]);
	// 	printf("is builtin : %d\n", (*cmd + i)->built_in);
	// 	printf("input is : %s\n", (*cmd + i)->info[0]);
	// 	printf("output is : %s\n", (*cmd + i)->info[1]);
	// 	printf("del is : %s\n", (*cmd + i)->info[2]);
	// 	printf("output_append is : %s\n", (*cmd + i)->info[3]);
	// }
	free(nodes);
	return (0);
}

int	display(t_sys_info *info, t_mini *c)
{
	t_command	*cmd;
	char		*line;
	int			i;

	line = NULL;
	while (1)
	{
		//ft_memset(line, 0, ft_strlen(line));
		line = readline("🚨🚨🚨🚨🚨🚨애애애애애앵‼️‼️‼️‼️‼️‼️🚨🚨🚨🚨🚨🚨📢📢📢📢📢📢📢긴급상황‼️‼️‼️긴급상황‼️‼️‼️‼️‼️📢📢📢📢📢📢📢🔊🔊🔊🔊🔊🔊‼️‼️‼️🔊🔊🔊🔊🔊🔊🔊🔊🔊🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🛎🛎🛎🛎🛎🛎🛎모두주목해주세요땡땡땡땡땡🛎🛎🛎🛎🛎🎤🎤🎤🎤아아-마이크테스트-!마이크테스트-!🎤🎤🎤🎤🎙🎙🎙🎙🎙마이크테스트— 들린다면 응답하라—-🎙🎙🎙🎙🎙📣📣📣📣📣📣📣 ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			info->cmd_cnt = pipe_cnt(line) + 1;
			cmd = ft_calloc(sizeof(t_command), info->cmd_cnt);
			i = -1;
			while (++i < info->cmd_cnt)
				ft_memset(cmd + i, 0, sizeof(t_command));
			tokenize(line, &cmd, info);
			i = -1;
			while (++i < info->cmd_cnt)
			{
				if (cmd[i].info[0])
					cmd[i].input = cmd[i].info[0];
				if (cmd[i].info[1])
					cmd[i].output = cmd[i].info[1];
				if (cmd[i].info[2])
					cmd[i].delimiter = cmd[i].info[2];
				if (cmd[i].info[3])
					cmd[i].output_append = cmd[i].info[3];
			}
			_jungyeok(cmd, c, info->cmd_cnt - 1);
			ft_free_command(&cmd, info);
		}
	}
	return (0);
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

int	main(int ac, char **av, char **envp)
{
	t_sys_info	info;
	t_mini		c;
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	main_init(ac, av);
	ft_memset(&c, 0, sizeof(t_mini));
	c.index = 0;
	while (envp[c.index])
		c.index++;
	c.env = ft_calloc(8, c.index + 1);
	c.index = -1;
	while (envp[++c.index])
		c.env[c.index] = ft_strdup(envp[c.index]);
	display(&info, &c);
	(void)av;
	c.index = -1;
	while (c.env[++c.index])
		free(c.env[c.index]);
	free(c.env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}
