/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:40:20 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/30 19:30:30 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
#include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *s){
	int	i = 0;
	if (s)
		while(s[i])
			i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd){
	write(fd, s, ft_strlen(s));
}
*/

int	_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 0);
	write(1, pwd, ft_strlen(pwd));
	write(1, "\n", 1);
	free(pwd);
	return (0);
}

/*
int	main(){
	_pwd();
}
*/
