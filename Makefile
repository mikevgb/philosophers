# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 21:54:22 by mvillaes          #+#    #+#              #
#    Updated: 2021/06/18 18:14:11 by mvillaes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	main.c \
		parse.c \
		thread.c \
		./utils/ft_putstr.c \
		./utils/ft_isdigit.c \
		./utils/ft_bzero.c \
		./utils/atoi_tuned.c


OBJ = $(SRC:.c=.o)

CFLAG = -Wall -Werror -Wextra

SANIT = -g3 -fsanitize=address

$(NAME):
	gcc $(CFLAG) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

debug:
	gcc $(CFLAG) $(SANIT) $(SRCS) -o $(NAME)

re: fclean all

.PHONY: all clean fclean re