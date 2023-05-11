/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:25:38 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/11 16:35:35 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "header.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_command
{
	bool			built_in;
	char			**cmd;
	char			*input;
	char			*output;
	char			*delimiter;
	char			*output_append;
	char			*unit;
	char			**info;
}					t_command;

typedef struct s_mini
{
	pid_t			pid;
	int				cmd_cnt;
	char			**env;
	char			**path;
	char			*cmd;
	int				ncmd;
	int				*pipe;
	int				fd_in;
	int				fd_out;
	int				index;
	int				dollar;
	int				hered;
	int				is_two;
}					t_mini;

#endif
