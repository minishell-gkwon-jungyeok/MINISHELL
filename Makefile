# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edwin <edwin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 23:31:55 by edwin             #+#    #+#              #
#    Updated: 2023/04/20 22:45:34 by jungyeok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
LDFLAGS		=	-L/opt/homebrew/opt/readline/lib -lreadline
CPPFLAGS	=	-I/opt/homebrew/opt/readline/include

SRCS = 	src/main.c\
		src/ft_split.c\
		src/minishell_utils.c
		
OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# colors

DEF_COLOR   =   \033[0;39m
CYAN        =   \033[3;96m
GREEN       =   \033[1;92m
MAGENTA     =   \033[3;95m
YELLOW      =   \033[1;93m
BLUE        =   \033[1;94m
GRAY        =   \033[2;90m

clean	:
			@rm -f $(OBJS)
			@echo "${CYAN}object files cleaned !${DEF_COLOR}"

fclean	:	clean
			@rm -f $(NAME)
			@echo "${MAGENTA}${NAME} excutable file cleaned !${DEF_COLOR}"

re		:	fclean
			@$(MAKE) all
			@echo "${BLUE}Cleaned and Rebuilt all files !${DEF_COLOR}"

.PHONY: all re fclean clean bonus
