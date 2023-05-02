/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/02 21:39:32 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokenize(char *line, t_command **cmd, t_sys_info *info)
{
	char	**nodes;
	int		i;
	int		j;

	i = -1;
	nodes = ft_split(line, '|');
	is_valid_quote(nodes);
	if (!nodes[0])
	{
		free(nodes);
		return (0);
	}
	while (++i < info->cmd_cnt)
		init_cmd(nodes[i], cmd[i]);
	builtin_check(cmd, info);
	i = -1;
	while (++i < info->cmd_cnt)
	{
		j = -1;
		while (cmd[i]->program[++j])
			printf("program is : %s\n", cmd[i]->program[j]);
		printf("is builtin : %d\n", cmd[i]->built_in);
		printf("input is : %s\n", cmd[i]->info[0]);
		printf("output is : %s\n", cmd[i]->info[1]);
		printf("del is : %s\n", cmd[i]->info[2]);
		printf("output_append is : %s\n", cmd[i]->info[3]);
	}
	free(nodes);
	return (0);
}

int	display(t_sys_info *info, char ***envp)
{
	t_command	**cmd;
	char		*line;
	int			i;

	set_signal_handlers();
	while (1)
	{
		line = readline("bash-3.3$ ");
		if (ft_strncmp(line, "\0", 1))
		{
			if (!ft_strncmp(line, "exit", 4))
				ft_exit(0);
			info->cmd_cnt = pipe_cnt(line) + 1;
			cmd = ft_calloc(sizeof(t_command *), info->cmd_cnt);
			i = 0;
			while (i < info->cmd_cnt)
				cmd[i++] = ft_calloc(sizeof(t_command), 1);
			tokenize(line, cmd, info);
			add_history(line);
			(void) envp;
			//_jungyeok(&command, envp);
			ft_free_command(cmd, info);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sys_info	info;

	if (ac != 1)
		return (1);
	display(&info, &envp);
	(void)av;
	return (0);
}
