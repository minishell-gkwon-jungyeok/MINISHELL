/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:00:27 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/11 17:29:03 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	_124(char *s)
{
	int	i;

	if (s[0] == 124)
		return (true);
	i = 0;
	while (s[i] && s[i + 1])
	{
		if (s[i] == 124 && s[i + 1] == 124)
			return (true);
		i++;
	}
	return (false);
}

void	display(t_mini *c)
{
	t_command	*cmd;
	char		*line;

	while (1)
	{
		line = readline("jungkwon$ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			if (_124(line))
				continue ;
			add_history(line);
			if (pipe_split(&line, &cmd, c))
				continue ;
			c->cmd_cnt = c->ncmd;
			env_change(&cmd, c->env, c->ncmd);
			bracket_remove(&cmd, c->ncmd);
			_32split(&cmd, c->ncmd);
			_3439to7(&cmd, c->ncmd);
			is_builtin(&cmd, c->ncmd);
			_jungyeok(cmd, c, c->ncmd - 1);
			ft_free_command(&cmd, c);
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

	(void) av;
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
