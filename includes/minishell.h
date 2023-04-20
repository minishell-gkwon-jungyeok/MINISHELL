/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:06 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/21 00:33:26 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "header.h"
# include "struct.h"
# include "../src/jungyeok/jungyeok.h"

# define PIPE 3
# define COMMAND 4
# define OPTION 5
# define STDIN 6
# define S_QUOT 7
# define D_QUOT 8
# define REDIREC 9
# define SEMICLON 10
# define BACKSLASH 11

/* basic functions */
char	**ft_split(char const *s, char c);
int		tokenize(char *line);
void	write_prompt(void);
int		start_shell(char **envp);
int		ft_strlen(char *str);

#endif
