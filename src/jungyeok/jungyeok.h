/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jungyeok.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:06:25 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 22:29:40 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JUNGYEOK_H
# define JUNGYEOK_H

# include "../../includes/header.h"
# include "../../includes/struct.h"

/* jungyeok.c */
int	_jungyeok(t_command **command, char **envp);

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

	/* built in functions */
/* echo.c */
/* cd.c */
/* pwd.c */
/* export.c */
/* unset.c */
/* env.c */
/* exit.c */
#endif
