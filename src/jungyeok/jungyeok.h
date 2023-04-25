/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:06:25 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/25 07:13:06 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JUNGYEOK_H
# define JUNGYEOK_H

# include "../../includes/header.h"
# include "../../includes/struct.h"

/* jungyeok.c */
int		_jungyeok(t_command **command, char **envp);

/* input.c */
int		_err_hd(char *s);
int		_heredoc(char *s, t_mini *c);

/* pipe.c */
int		close_pipe(t_mini *c, int opened);
int		open_pipe(t_mini *c, int npipe);

/* command.c */
int		command_access(char **path, t_command *cmd, t_mini *c);

/* err.c */
int		_err(char *s);

/* ft_fd.c */
void	ft_putstr_fd(char *s, int fd);
void	ft_char_fd(char c, int fd);

/* basic.c */
int		ft_strcmp(char *s1, char *s2);

	/* builtin */
/* echo.c */
int		_echo(t_command *cmd, int fd);

/* cd.c */
int		_cd(t_command *cmd, int fd);

/* pwd.c */
int		_pwd(int fd);

/* export.c */
int		_export(t_command *cmd, char ***env, int fd);

/* unset.c */
int		_unset(t_command *cmd, char ***env);

/* env.c */
int		_env(char **env, int fd);

/* exit.c */
void	__exit(t_command *cmd);

#endif
