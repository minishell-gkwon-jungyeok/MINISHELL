/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:06 by gkwon             #+#    #+#             */
/*   Updated: 2023/05/11 17:33:57 by gkwon            ###   ########.fr       */
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

/* FOR BASIC3 */
# define IN 0
# define JN 1
# define LEN 2
# define NC 3

/* FOR ENV_CHANGE */
# define N34 0
# define N39 1

# define OUQ 0
# define INQ 1

# define JNDEX 0
# define CURRENT 1
# define LENGTH 2

/* ===============../src=============== */

/* main.c */
int		tokenize(char *line, t_command **cmd, t_mini *c);
void	display(t_mini *c);
int		is_valid_line_check(char *line);

/* basic1.c */
int		ft_strlen(char *s);
void	*ft_memset(void *b, int c, int len);
void	ft_err(char *s);
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *s);

/* basic2.c */
char	*ft_strjoin(char *s1, char *s2);
bool	ft_strncmp(char *s1, char *s2, int n);
int		ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memmove(void *dst, void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/* basic3.c */
int		ft_strlen_c(char *s, int c);
char	*ft_strdup_c(char *s, int c);
char	*ft_realloc_c(char *s, int c);
char	**split_jungyeok(char *s, int c);

/* ft_free.c */
void	ft_free_command(t_command **cmd, t_mini *c);
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
void	parse(char **line, t_mini *c);

/* src/parse_quote_util.c */
int		doller_parse_with_del_quot(char ***nodes, t_mini *c);

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

/* =================../src/gyeom================= */
int		pipe_split(char **line, t_command **cmd, t_mini *c);

char	**split_gyeom(char *s, int c);

bool	if_in34(char *s, int cur);
bool	if_in39(char *s, int cur);
void	env_change(t_command **cmd, char **env, int ncmd);

void	bracket_remove(t_command **cmd, int ncmd);
void	check3439(int n[2], char *s, int i);
char	*ft_strdup3439(char *s, int *len);

void	_3439to7(t_command **cmd, int ncmd);

void	_32split(t_command **cmd, int ncmd);

void	is_builtin(t_command **cmd, int ncmd);

#endif
