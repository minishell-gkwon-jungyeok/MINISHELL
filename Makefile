# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edwin <edwin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 23:31:55 by edwin             #+#    #+#              #
#    Updated: 2023/04/19 23:41:49 by edwin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS=-L/opt/homebrew/opt/readline/lib -lreadline
CPPFLAGS=-I/opt/homebrew/opt/readline/include
SRCS = 	src/main.c\
		src/ft_split.c\
		src/minishell_utils.c
		
OBJS=$(SRCS:.c=.o)

NAME=minishell

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all re fclean clean bonus