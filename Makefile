CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
LDFLAGS		=	-L/opt/homebrew/opt/readline/lib -lreadline
CPPFLAGS	=	-I/opt/homebrew/opt/readline/include

SRCS = 	src/main_jungyeok.c\
		src/ft_split.c\
		src/minishell_utils.c\
		src/basic1.c src/basic2.c\
		src/jungyeok/jungyeok.c src/jungyeok/err.c\
		src/jungyeok/input.c\
		src/jungyeok/pipe.c src/jungyeok/command.c\
		src/jungyeok/basic.c\
		src/jungyeok/builtin/cd.c\
		src/jungyeok/builtin/echo.c\
		src/jungyeok/builtin/env.c\
		src/jungyeok/builtin/exit.c\
		src/jungyeok/builtin/export.c\
		src/jungyeok/builtin/pwd.c\
		src/jungyeok/builtin/unset.c\

OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

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
