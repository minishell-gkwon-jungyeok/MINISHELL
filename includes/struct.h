/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungyeok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:25:38 by jungyeok          #+#    #+#             */
/*   Updated: 2023/04/21 00:27:44 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "header.h"

typedef struct s_token
{
	int				type;
	char			*str;
	struct s_token	*pre;
	struct s_token	*next;
}t_token;

typedef struct s_command
{
	bool	built_in;	//echo, cd, pwd, export, unset, env, exit
	char	**program;
	char	*input;
	char	*output;
	char	*delimiter;
	char	*output_append;
}t_command;

#endif
