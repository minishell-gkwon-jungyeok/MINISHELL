/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edwin <edwin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 19:05:06 by gkwon             #+#    #+#             */
/*   Updated: 2023/04/20 22:24:05 by jungyeok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>

# define PIPE 3
# define COMMAND 4
# define OPTION 5
# define STDIN 6
# define S_QUOT 7
# define D_QUOT 8
# define REDIREC 9
# define SEMICLON 10
# define BACKSLASH 11

typedef struct s_token
{
	int					type;
	char				*str;
	struct s_token		*pre;
	struct s_token		*next;
}t_token;

typedef struct s_command
{
	bool	built_in;			//echo, cd, pwd, export, unset, env, exit
	char	**program;
	char	*input;
	char	*output;
	char	*delimiter;
	char	*output_append;
}t_command;

/* ===============.=============== */

char			**ft_split(char const *s, char c);
int	tokenize(char *line);
void			write_prompt(void);
int				start_shell(char **envp);

#endif
