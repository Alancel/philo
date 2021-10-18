# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alancel <alancel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/08 19:49:16 by alancel           #+#    #+#              #
#    Updated: 2021/10/08 19:51:59 by alancel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=src/init.c src/philo.c src/print.c src/runtime_functions.c src/runtime.c src/utils.c

FLAGS=-Wextra -Wall -Werror

NAME=philo

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

re: fclean $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
