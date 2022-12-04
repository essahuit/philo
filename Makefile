# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kessalih <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 09:50:35 by kessalih          #+#    #+#              #
#    Updated: 2022/07/20 09:50:40 by kessalih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CFILES = main.c check.c parsing.c routin.c time.c
OFILES = $(CFILES:.c=.o)
CC = gcc
RM = rm -rf
AR = ar rcs
FLAGS = -Wall -Werror -Wextra
NAME = philo.a

%.o : %.c
	$(CC) $(FLAGS) $< -c
	$(AR) $(NAME) $@

$(NAME) : $(OFILES)
	$(CC) $(FLAGS) main.c  $(NAME) -lpthread -o philo

all : $(NAME)

clean :
	$(RM) $(OFILES)     

fclean :
	$(RM) $(NAME) $(OFILES) philo

re : fclean all