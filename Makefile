CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g #-fsanitize=address
LDFLAGS		=	-lreadline -L${HOME}/.brew/opt/readline/lib/
CPPFLAGS	=	-I${HOME}/.brew/opt/readline/include/

SRCS = 	src/main.c\
		src/ft_split.c\
		src/basic1.c\
		src/basic2.c\
		src/basic3.c\
		src/ft_free.c\
		src/init_cmd.c\
		src/parse_quote.c\
		src/parse_quote_util.c\
		src/parse_util.c\
		src/signal.c\
		src/standard_split.c\
		src/jungyeok/jungyeok.c src/jungyeok/err.c\
		src/jungyeok/input.c\
		src/jungyeok/output.c\
		src/jungyeok/pipe.c\
		src/jungyeok/command.c\
		src/jungyeok/_cmd_env.c\
		src/jungyeok/basic.c\
		src/jungyeok/basicc.c\
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
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)
	@echo "${YELLOW}All files are compiled !!${DEF_COLOR}"
	@echo "✅ ${GREEN}Minishell executable file made !${DEF_COLOR}"

%.o : %.c
	@echo "${GRAY}compiling $<...${DEF_COLOR}"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
