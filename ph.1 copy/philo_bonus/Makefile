# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alancel <alancel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 19:32:09 by alancel           #+#    #+#              #
#    Updated: 2021/10/11 19:32:47 by alancel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=src/init.c src/philo_bonus.c src/print.c src/runtime_functions.c src/runtime.c src/utils.c

FLAGS=-Wextra -Wall -Werror

NAME=philo_bonus

$(NAME):
	gcc $(FLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

re: fclean $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
