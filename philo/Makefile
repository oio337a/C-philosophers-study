# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/03 15:23:57 by yongmipa          #+#    #+#              #
#    Updated: 2023/04/14 17:54:31 by yongmipa         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -MP -pthread

SRCS = 	main.c utils.c validate.c

NAME = philo

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

all : $(NAME)

$(NAME) : $(OBJS)

clean :
	$(RM) $(OBJS) $(DEPS)

fclean : clean
	$(RM) $(NAME)
	
re : 
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re