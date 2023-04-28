CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address
LDFLAGS		=	-lreadline -L/opt/homebrew/opt/readline/lib 
CPPFLAGS	=	-I/opt/homebrew/opt/readline/include

SRCS = 	src/main.c\
		src/ft_split.c\
		src/minishell_utils.c\
		src/basic1.c\
		src/basic2.c
		#src/jungyeok/jungyeok.c src/jungyeok/err.c\
		
OBJS	=	$(SRCS:.c=.o)

NAME	=	minishell

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

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
