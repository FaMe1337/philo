# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: famendes <famendes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/20 14:26:29 by famendes          #+#    #+#              #
#    Updated: 2024/12/20 14:31:47 by famendes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	main.c\
		parsing.c\
		init.c\
		dinner.c\
		dinner_utils.c\
		controls.c\
		monitor.c\
		errors_and_clean.c\

OBJ = $(SRCS:.c=.o)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all
