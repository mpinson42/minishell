NAME = minishell

SRC = srcs/ft_dev.c srcs/main.c srcs/ft_setenv.c srcs/ft_unsetenv.c srcs/ft_env.c srcs/ft_echo.c srcs/ft_cd.c srcs/ft_check.c srcs/ft_outils.c srcs/ft_setup.c

FLAGS = -Wall -Wextra -Werror

SRC2 = dev.o srcs.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@cp ./libft/libft.a ./lib
	gcc $(FLAGS) -I ./include/ -L ./lib -lft -o $(NAME) $(SRC)


clean:
	/bin/rm -f $(SRC2)
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
