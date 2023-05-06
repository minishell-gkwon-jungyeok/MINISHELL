/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:25:38 by jungyeok          #+#    #+#             */
/*   Updated: 2023/05/05 21:47:32 by edwin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "header.h"

typedef struct s_sys_info
{
	int		cmd_cnt;
}t_sys_info;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list;

typedef struct s_command
{
	bool	built_in;
	char	**cmd;
	char	*input;
	char	*output;
	char	*delimiter;
	char	*output_append;
	char	**info;
}t_command;

typedef struct s_mini
{
	pid_t	pid;
	char	**env;
	char	**path;
	char	*cmd;
	int		ncmd;
	int		*pipe;
	int		fd_in;
	int		fd_out;
	int		index;
	int		dollar;
	int		hered;
}t_mini;

#endif
