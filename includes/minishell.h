/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:06 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/23 03:21:47 by gkwon            ###   ########.fr       */
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

/* functions of GKWON*/
int		tokenize(char *line, t_command **cmd, t_sys_info *info);
void	write_prompt(void);
int		start_shell(char **envp);

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* basic1.c */
int		ft_strlen(char *str);
void	*ft_memset(void *b, int c, int len);
void	*ft_calloc(int count, int size);
void	ft_err(char *s);
char	*ft_strdup(char *s);

/* basic2.c */
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
