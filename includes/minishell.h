/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:06 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/09 16:36:15 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/jungyeok/jungyeok.h"
# include "header.h"
# include "struct.h"

# define PIPE 3
# define COMMAND 4
# define OPTION 5
# define STDIN 6
# define S_QUOT 7
# define D_QUOT 8
# define REDIREC 9
# define SEMICLON 10
# define BACKSLASH 11
# define SHE 0
# define DFL 1
# define IGN 2

/* ===============../src=============== */

/* main.c */
int		tokenize(char *line, t_command **cmd, t_sys_info *info, char **env);
void	display(t_sys_info *info, t_mini *c);

/* basic1.c */
int		ft_strlen(char *s);
void	*ft_memset(void *b, int c, int len);
void	ft_err(char *s);
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *s);

/* basic2.c */
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memmove(void *dst, void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* ft_free.c */
void	ft_free_command(t_command **cmd, t_sys_info *info);
void	ft_exit(int return_val);

/* ft_split.c */
char	**ft_split(char const *s, char c);

/* init_cmd.c */
void	init_cmd(char *node, t_command *cmd);
void	builtin_check(t_command *cmd, int cmd_cnt);

/* signal.c */
void	handle_signal(int signum);
void	set_signal_handlers(void);

/* parse_quote.c */
int		is_ended_quote(char **nodes, int i, int j);
int		parse_set_quotes(char *line, int quotes);
void	parse(char **line, char **env);

/* src/parse_quote_util.c */
int		doller_parse_with_del_quot(t_command *cmd, t_sys_info *info,
			char **env);

/* standard_split.c */
char	**std_split(char const *s, char c);

/* parse_util.c */
int		pipe_cnt(char *line);
bool	get_env_val(char **s, char **env, char **target_val);
char	*ft_substr(char *s, int start, int len);
bool	bool_strncmp(const char *s1, const char *s2, size_t n);
char	*replace_middle(char *s1, int start, int len, char *s2);

/* jungyeok/basicc.c */
int		ft_getindex(char *s, int c);

/* ===============../src/jungyeok=============== */

int		_jungyeok(t_command *command, t_mini *c, int npipe);

#endif
