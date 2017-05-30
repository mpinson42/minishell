NAME = minishell

SRC = srcs/ft_dev.c srcs/main.c 

FLAGS = -Wall -Wextra -Werror

SRC2 = dev.o srcs.o

all: $(NAME)

%.o : %.c
	gcc -c -o $@ $^

$(NAME): $(SRC)
	@echo "mpinson" > auteur
	@make -C ./libft all
	@cp ./libft/libft.a ./lib
	gcc -I ./include/ -L ./lib -lft -o $(NAME) $(SRC)


clean:
	/bin/rm -f $(SRC2)
	@make -C ./libft clean

fclean: clean
	/bin/rm -f $(NAME)
	@make -C ./libft fclean

re: fclean all
