CC = cc

INCLUDE = -Isrcs -Iparsing

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -fsanitize=address

SRC = srcs/mini_shell.c libft/ft_strlen.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c \
	libft/ft_putstr_fd.c execution/signals/signals.c execution/built-ins/echo_cmd.c execution/built-ins/cd_cmd.c \
	execution/built-ins/pwd_cmd.c execution/built-ins/exit_cmd.c execution/built-ins/env_cmd.c libft/ft_lstadd_back.c \
	libft/ft_lstlast.c libft/ft_strcmp.c execution/built-ins/unset_cmd.c parsing/tokenizer.c parsing/parsing.c \
	execution/built-ins/export_cmd.c libft/ft_isdigit.c libft/ft_atoi.c helping_func/ft_perror.c execution/built-ins/built_ins.c \
	execution/shell_setup/setup_shell_env.c execution/execute/execution.c execution/shell_setup/path_resolver.c libft/ft_strchr.c \
	parsing/build_tree.c execution/execute/pipe_execution.c parsing/utils_parsing.c	parsing/utils_tokinizer.c \
	execution/redirections/red_input.c execution/redirections/red_output.c execution/redirections/heredoc.c \
	execution/redirections/red_append.c execution/redirections/redirections.c execution/redirections/red_in_out.c \
	parsing/expand.c execution/redirections/heredoc_utils.c libft/ft_itoa.c execution/built-ins/built_in_utils.c \
	libft/ft_isalpha.c libft/ft_isalnum.c execution/redirections/red_heredoc.c libft/ft_memset.c

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
# .SECONDRY: $(NAME) $(OBJ)
# .SECONDRY: $(OBJ)	# >>> to check the relink litter on.
.INTERMEDIATE: $(OBJ)	# >>> to romove this litter on.