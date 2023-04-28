/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/28 19:35:11 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_cnt(char *line)
{
	int	cnt;

	cnt = 0;
	while (*line)
	{
		if (*line == '|')
			cnt++;
		line++;
	}
	return (cnt);
}

void	init_cmd(char *node, t_command *cmd)
{
	const static char	*string_table[] = {"<", ">", "<<", ">>"};
	int					i;
	int					at;
	int					end;
	int					len;
	int					tmp;
	char				*ret;

	if (!node)
	{
		//ft_heardoc();
		return ;
	}
	i = -1;
	cmd->info = ft_calloc(sizeof(char *), 4);
	while (++i < 4)
		cmd->info[i] = ft_calloc(sizeof(char), 1);
	i = 0;
	while (i < 4)
	{
		len = 0;
		at = ft_strnstr(node, string_table[i], ft_strlen(node));
		end = at;
		if (at != -1 && node[at
				+ ft_strlen((char *)string_table[i])] != string_table[i][0])
		{
			if (i < 2)
				end++;
			else
				end += 2;
			while (node[end] == ' ')
				end++;
			while (node[end + len] != ' ' && node[end + len] != 0 && node[end
					+ len] != '<' && node[end + len] != '>')
				len++;
			if (cmd->info[i][0])
			{
				ret = malloc(len + 2);
				ret[len] = 0;
				ret[0] = ' ';
				ft_memmove(ret + 1, node + end, len);
				cmd->info[i] = ft_strjoin(cmd->info[i], ret);
			}
			else
			{
				cmd->info[i] = ft_calloc(len + 1, 1);
				cmd->info[i][len] = 0;
				ft_memmove(cmd->info[i], node + end, len);
			}
			tmp = ft_strlen(&node[len]);
			ft_strlcpy(node + at, node + end + len, tmp);
			node[at] = 0;
		}
		else
			i++;
	}
	cmd->program = ft_split(node, ' ');
	free(node);
}

void	builtin_check(t_command **cmd, t_sys_info *info)
{
	const static char	*string_table[] = {"cd", "echo",
		"env", "exit", "export", "pwd", "unset"};
	int					i;
	int					j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		if (!cmd[i]->program)
		{
			i++;
			continue ;
		}
		j = 0;
		while (j < 7)
		{
			if (ft_strnstr(cmd[i]->program[0], string_table[j], ft_strlen(cmd[i]
						->program[0])) > -1)
						if (ft_strlen(cmd[i]->program[0]) == ft_strlen((char *)string_table[j]))
							cmd[i]->built_in = true;
			j++;
		}
		i++;
	}
}

int	parse_set_quotes(char line, int quotes)
{
	int	result;

	result = quotes;
	if (line == '\'')
	{
		if (quotes == 1)
			result = 0;
		else if (quotes == 2)
			result = 2;
		else
			result = 1;
	}
	else if (line == '\"')
	{
		if (quotes == 2)
			result = 0;
		else if (quotes == 1)
			result = 1;
		else
			result = 2;
	}
	return (result);
}

int	ft_line_quote(char *line)
{
	int at;
	int	quotes;

	at = 0;
	quotes = 0;
	while (line[at])
	{
		quotes = parse_set_quotes(line[at], quotes);
		at++;
	}
	if (quotes != 0) // 닫히지 않은 따옴표 예외처리
	{
		printf("test exit: quotes error\n");
		exit(1);
	}
}

int	tokenize(char *line, t_command **cmd, t_sys_info *info)
{
	char	**nodes;
	int		i;
	int		j;

	i = -1;
	ft_line_qoute(line);
	nodes = ft_split(line, '|');
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

void	ft_free_command(t_command **cmd, t_sys_info *info)
{
	int			i;
	int			j;

	i = 0;
	while (i < info->cmd_cnt)
	{
		j = 0;
		if (cmd[i]->program[j])
			while (cmd[i]->program[j])
				free(cmd[i]->program[j++]);
		free(cmd[i]->program);
		j = -1;
		while (++j < 4)
			if (cmd[i]->info[j])
				free(cmd[i]->info[j]);
		free(cmd[i]->info);
		i++;
	}
	free(cmd);
}

void handle_signal(int signum)
{
    if (signum == SIGINT)
    {
		printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    // else if (signum == SIGQUIT)
    // {
    //     if (is_in_heardoc)
	// 		write(1, "^\\Quit: 3\n", 10);
    // }
    else if (signum == -1)
    {
		write(1, "exit\n", 5);
    	exit(0);
    }
}

void set_signal_handlers()
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
    signal(-1, handle_signal);
}

void	ft_exit(int return_val)
{
	printf("exit\n");
	exit(return_val);
}

int	display(t_sys_info *info, char ***envp)
{
	t_command	**cmd;
	char		*line;
	int			i;
	//struct sigaction	sig;

	(void)envp;
	// sig.sa_flags = SA_SIGINFO;
	// sig.sa_sigaction = get_signal;
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
			//_jungyeok(&command, envp);
			ft_free_command(cmd, info);
		}
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sys_info	info;
	//int			pid;

	if (ac != 1)
		return (1);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	get_signal();
	// }
	// else
	// {
		display(&info, &envp);
	//}
	(void)av;
	return (0);
}
