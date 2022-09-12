CC = CC
NAME = minishell
FLAGS = -Wall -Wextra -Werror

SRC = libft/ft_strdup.c libft/ft_strjoin.c  libft/ft_strlen.c  libft/ft_split.c \
	libft/ft_strjoin_char.c libft/ft_lstadd_back.c libft/ft_lstnew.c libft/ft_lstlast.c \
	libft/ft_substr.c libft/ft_calloc.c libft/ft_strchr.c libft/ft_lstadd_back_env.c \
	libft/ft_lstnew_env.c libft/ft_lstlast_env.c libft/ft_isdigit.c libft/ft_putstr_fd.c \
	libft/ft_strcmp.c libft/ft_itoa.c\
	builtins/env.c builtins/export.c \
	minishell.c \
	src/syntaxe1_error.c src/syntaxe2_error.c src/disperse_cmd.c  src/utils.c src/utils_2.c src/pipe_cmd.c src/make_env.c\
	src/utils_disperse_cmd.c src/expend_herdog.c src/red_cmd.c src/herdog_utils.c \


OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ) minishell.h
		$(CC) $(SRC) -lreadline  -o   $(NAME)
%.o : %.c minishell.h
		$(CC) $(FLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all