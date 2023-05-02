/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 21:59:32 by edwin             #+#    #+#             */
/*   Updated: 2023/05/03 05:18:39 by gkwon            ###   ########.fr       */
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
	signal(SIGINT, terminal);
	signal(SIGQUIT, terminal);
}

void	terminal(int signum)
{
	struct termios org_term;
	struct termios new_term;

	tcgetattr(STDIN_FILENO, &org_term);
	
	tcgetattr(STDIN_FILENO, &new_term); // STDIN으로부터 터미널 속성을 받아온다
	new_term.c_lflag &= ~(ICANON | ECHO);  // ICANON, ECHO 속성을 off
	new_term.c_cc[VMIN] = 1;               // 1 바이트씩 처리
	new_term.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term); // 변경된 속성의 터미널을 STDIN에 바로 적용
	handle_signal(signum);
	
	tcsetattr(STDIN_FILENO, TCSANOW, &org_term);
}