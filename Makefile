CC = cc -g
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = srcs/mini_shell.c libft/ft_strlen.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c \
<<<<<<< HEAD
	libft/ft_putstr_fd.c execution/signals/signals.c execution/built-ins/echo_cmd.c \
	execution/built-ins/cd_cmd.c execution/built-ins/pwd_cmd.c execution/built-ins/exit_cmd.c execution/built-ins/env_cmd.c \
	libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_strcmp.c execution/built-ins/unset_cmd.c parsing/tokenizer.c parsing/parsing.c \
	execution/built-ins/export_cmd.c
=======
	libft/ft_putstr_fd.c execution/signals/signals.c execution/built-ins/env.c execution/built-ins/echo_cmd.c \
	execution/built-ins/cd_cmd.c execution/built-ins/pwd_cmd.c execution/built-ins/exit_cmd.c execution/built-ins/env_cmd.c \
<<<<<<< HEAD
	libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_strcmp.c execution/built-ins/unset_cmd.c
=======
	libft/ft_lstadd_back.c libft/ft_lstlast.c libft/ft_strcmp.c
>>>>>>> 4b13520 (update)
>>>>>>> 0ce570e13e4b0b223063194c26e845647d18e9d8

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
