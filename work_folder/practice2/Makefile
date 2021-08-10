# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/17 21:54:22 by mvillaes          #+#    #+#              #
#    Updated: 2021/07/31 22:38:30 by mvillaes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = 	philo.c \
		threads_mutex.c \
		utils.c \
		utils/atoi_tuned.c \
		utils/ft_bzero.c \
		utils/ft_isdigit.c \
		utils/ft_put.c

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

# rebug:
# 	fclean debug

re: fclean all

.PHONY: all clean fclean re