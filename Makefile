NAME		= minishell

CC			= gcc
AR			= ar rc
RM			= rm -f

_SRCS		= main.c process.c process_token.c builtins.c \
			  execute.c environ.c errors.c vars.c builtins_env.c \
			  token_utils.c pipes.c variables.c clean.c \
			  redirects.c signals.c terminal.c terminal_keys.c \
			  terminal_setup.c terminal_edit.c terminal_history.c
SRCS		= $(addprefix srcs/, $(_SRCS))

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

%.o: %.c
			$(CC) $(CFLAGS) -Iincludes -Ilibft -c $< -o $@

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(OBJS) -o $(NAME) -ltermcap -Llibft -lft

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

all:		$(NAME)

.PHONY: clean fclean re all
