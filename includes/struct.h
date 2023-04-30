/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkwon <gkwon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:25:38 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/30 15:59:05 by gkwon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "header.h"

typedef struct s_sys_info
{
	int	cmd_cnt;
	//so on..
}t_sys_info;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}t_list

typedef struct s_command
{
	bool	built_in;	//echo, cd, pwd, export, unset, env, exit
	t_list	*program;
	//char	*input;
	//char	*output;
	//char	*delimiter;
	//char	*output_append;
	char	**info;
}t_command;

typedef struct s_mini
{
	char	**path;
	int		ncmd;
	int		pipe[2];
}t_mini;

#endif
