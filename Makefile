CC = cc -g
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC = srcs/mini_shell.c libft/ft_strlen.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c \
	libft/ft_putstr_fd.c execution/built-ins/built-ins.c execution/signals/signals.c execution/built-ins/env.c \
	execution/built-ins/echo_cmd.c execution/built-ins/cd_cmd.c execution/built-ins/pwd_cmd.c

OBJ = $(SRC:.c=.o)
NAME = minishell
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re
.SECONDRY: $(NAME)
