CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mini_shell/mini_shell.c execution/built_in_cmds.c libft/ft_strlen.c libft/ft_split.c \
	libft/ft_strjoin.c libft/ft_strdup.c libft/ft_strncmp.c libft/ft_putstr_fd.c ft_printf/ft_printf.c \
	ft_printf/ft_putchar.c ft_printf/ft_putstr.c ft_printf/ft_putnbr.c ft_printf/ft_puthex.c \
	ft_printf/ft_putadd.c ft_printf/ft_putuint.c

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
