# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alancel <alancel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 20:45:58 by alancel           #+#    #+#              #
#    Updated: 2021/10/12 20:46:10 by alancel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS=src/init.c src/philo_bonus.c src/print.c src/runtime_functions.c src/runtime.c src/utils.c

FLAGS=-Wextra -Wall -Werror

NAME=philo_bonus

$(NAME):
	gcc  $(SRCS) -o $(NAME)

all: $(NAME)

re: fclean $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
