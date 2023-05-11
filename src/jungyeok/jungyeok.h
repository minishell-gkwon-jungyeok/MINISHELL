/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:06:25 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:30:14 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JUNGYEOK_H
# define JUNGYEOK_H

# include "../../includes/header.h"
# include "../../includes/struct.h"

/* jungyeok.c */
int		_jungyeok(t_command *command, t_mini *c, int npipe);

/* input.c */
int		_heredoc(char *s, t_mini *c);
int		_input(char *s, t_mini *c);
int		open_fd(t_command *command, t_mini *c);
void	fclose_pipe(t_mini *c, int index, int npip);

/* output.c */
int		_output(char *s, t_mini *c);
int		_output_append(char *s, t_mini *c);
void	close_fd(t_command *command, t_mini *c);

/* pipe.c */
int		close_pipe(t_mini *c, int opened);
int		open_pipe(t_mini *c, int npipe);

/* command.c */
void	command_access(char **path, t_command *cmd, t_mini *c);
void	_c_cmd(t_command *command, t_mini *c);
void	exe_builtin(char *s, t_command *command, t_mini *c);
void	_exe(t_command *command, t_mini *c);

/* err.c */
int		_err(char *s);

/* basic.c */
int		ft_strcmp(char *s1, char *s2);
char	*strjoin_jungyeok(char *s1, char *s2);
char	*ft_itoa(int n);

/* basicc.c */
char	*ft_strchr(char *s, int c);
int		ft_getindex(char *s, int c);
bool	ft_cmd(t_command *command, t_mini *c);

/* _cmd_env.c */
void	_cmd_env(t_command *command, char **env, t_mini *c);

	/* builtin */
/* echo.c */
int		_echo(t_command *cmd, t_mini *c);

/* cd.c */
int		_cd(t_command *cmd);

/* pwd.c */
int		_pwd(void);

/* export.c */
int		_export(t_command *cmd, char ***env);
bool	check61(char *s);
bool	check_env(char *s, char ***env);
void	_write(char *s);

/* unset.c */
int		_unset(t_command *cmd, char ***env);

/* env.c */
int		_env(char **env);

/* exit.c */
void	__exit(t_command *cmd, t_mini *c);

#endif
