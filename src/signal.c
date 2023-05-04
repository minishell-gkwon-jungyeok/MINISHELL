/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:59:32 by edwin             #+#    #+#             */
/*   Updated: 2023/05/03 18:47:59 by gkwon            ###   ########.fr       */
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
		//if (is_in_heardoc)
		write(1, "^\\Quit: 3\n", 10);
	}
}

void	set_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
