#!/bin/env python3
CC = cc

INCLUDE = -Isrcs

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) #-g3 -fsanitize=address

SRC = srcs/mini_shell.c libft/ft_strlen.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c \
	libft/ft_putstr_fd.c execution/built-ins/echo_cmd.c execution/built-ins/cd_cmd.c execution/execute/signals.c \
	execution/built-ins/pwd_cmd.c execution/built-ins/exit_cmd.c execution/built-ins/env_cmd.c libft/ft_lstadd_back.c \
	libft/ft_lstlast.c libft/ft_strcmp.c execution/built-ins/unset_cmd.c parsing/tokenizer.c parsing/parsing.c libft/ft_strnstr.c \
	execution/built-ins/export_cmd.c libft/ft_isdigit.c helping_func/ft_perror.c execution/built-ins/built_ins.c \
	execution/shell_setup/setup_shell_env.c execution/execute/execution.c execution/shell_setup/path_resolver.c libft/ft_strchr.c \
	parsing/build_tree.c execution/execute/pipe_execution.c parsing/utils_parsing.c	parsing/utils_tokinizer.c libft/ft_substr.c \
	execution/redirections/red_input.c execution/redirections/red_output.c execution/redirections/heredoc.c \
	execution/redirections/red_append.c execution/redirections/redirections.c helping_func/ft_char_to_str.c \
	parsing/expand.c execution/redirections/heredoc_utils.c libft/ft_itoa.c execution/built-ins/built_in_utils.c \
	libft/ft_isalpha.c libft/ft_isalnum.c execution/redirections/red_heredoc.c libft/ft_memset.c execution/redirections/heredoc_expand.c \
	execution/built-ins/export_utils.c helping_func/gc_manger.c helping_func/export_func.c helping_func/exit_msgs.c \
	helping_func/update_exec_envp.c execution/execute/pipe_utils.c execution/execute/signals_utils.c helping_func/heredoc_func.c \
	parsing/utils_expand.c parsing/utils_is_split1.c parsing/utils_is_split2.c parsing/utils_parsing2.c parsing/utils_parsing3.c parsing/utils_parsing4.c \
    parsing/utils_tokinizer2.c parsing/utils_tokinizer3.c parsing/utils_tokinizer4.c parsing/utils_tokinizer5.c \
	libft/ft_strcpy.c libft/ft_strcat.c libft/ft_strncpy.c
	

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