CC = cc

INCLUDE = -Isrcs -Iparsing

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -fsanitize=address

SRC = srcs/mini_shell.c libft/ft_strlen.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c \
	libft/ft_putstr_fd.c execution/signals/signals.c execution/built-ins/echo_cmd.c execution/built-ins/cd_cmd.c \
	execution/built-ins/pwd_cmd.c execution/built-ins/exit_cmd.c execution/built-ins/env_cmd.c libft/ft_lstadd_back.c \
	libft/ft_lstlast.c libft/ft_strcmp.c execution/built-ins/unset_cmd.c parsing/tokenizer.c parsing/parsing.c \
	execution/built-ins/export_cmd.c libft/ft_isdigit.c libft/ft_atoi.c execution/ft_perror.c execution/built-ins/built_ins.c \
	execution/shell_setup/setup_shell_env.c execution/shell_setup/heredoc.c execution/shell_setup/execution.c \
	execution/shell_setup/path_resolver.c libft/ft_strnstr.c

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
