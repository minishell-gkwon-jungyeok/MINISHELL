/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:59:32 by edwin             #+#    #+#             */
/*   Updated: 2023/05/10 17:48:21 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

//void handle_signal(int signum, siginfo_t *info, void *data)
//{
//	t_mini *c = (t_mini *)data;
//	(void)info;
//    if (signum == SIGINT)
//	{
//		if (c->hered)
//		{
//			c->is_two = 1;
//		}
//		printf("\n");
//		rl_on_new_line();
//		rl_replace_line("", 0);
//		rl_redisplay();
//	}
//	else if (signum == SIGQUIT && !c->hered)
//	{
//		rl_on_new_line();
//		rl_redisplay();
//	}
//}

//void set_signal_handlers(t_mini *c)
//{
//    struct sigaction sa;
//    sa.sa_sigaction = handle_signal;
//    sa.sa_flags = SA_SIGINFO;
//    sigemptyset(&sa.sa_mask);

//    sigaction(SIGINT, &sa, NULL);
//    sigaction(SIGQUIT, &sa, NULL);
//}