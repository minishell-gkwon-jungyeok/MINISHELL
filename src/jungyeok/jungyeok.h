/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:06:25 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/29 04:48:11 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JUNGYEOK_H
# define JUNGYEOK_H

# include "../../includes/header.h"
# include "../../includes/struct.h"

/* jungyeok.c */
int		_jungyeok(t_command *command, char **envp, int npipe);

/* heredoc.c */
int		_err_hd(char *s);
int		_heredoc(char *s, t_mini *c);

/* pipe.c */
int		close_pipe(t_mini *c, int opened);
int		open_pipe(t_mini *c, int npipe);
void	_dup2(int i, int j);

/* command.c */
void	command_access(char **path, t_command *cmd, t_mini *c);
void	_c_cmd(t_command *command, t_mini *c);
void    _exe(t_command *command, t_mini *c);

/* err.c */
int		_err(char *s);

/* ft_fd.c */
void	ft_putstr_fd(char *s, int fd);
void	ft_char_fd(char c, int fd);

/* basic.c */
int		ft_strcmp(char *s1, char *s2);

	/* builtin */
/* echo.c */
int		_echo(t_command *cmd);

/* cd.c */
int		_cd(t_command *cmd);

/* pwd.c */
int		_pwd(void);

/* export.c */
int		_export(t_command *cmd, char ***env);

/* unset.c */
int		_unset(t_command *cmd, char ***env);

/* env.c */
int		_env(char **env);

/* exit.c */
void	__exit(t_command *cmd);

#endif
