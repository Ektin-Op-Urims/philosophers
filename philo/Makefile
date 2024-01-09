# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 14:17:28 by Ektin Op Urims    #+#    #+#              #
#    Updated: 2023/10/28 23:07:06 by Ektin Op Urims   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo.c \
	philo_aux.c \
	data.c \
	routine.c \
	routine_utils.c \
	get_protected_values.c \

HEADERS = philo.h \

OBJS = $(SRCS:.c=.o)

NAME = philo

NORM = /bin/norminette

CFLAGS += -Wall -Wextra -Wpedantic -Werror -pthread
#CFLAGS += -fsanitize=thread -g

CC = gcc

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	make NORM

%.o:	%.c
	$(CC) -o $@ -c $< $(CFLAGS)

NORM:
	@if [ "$(wildcard $(NORM))" != "" ]; then \
		$(NORM) $(SRCS) $(HEADERS); \
	fi

clean:
	@rm -f $(wildcard *.o)

fclean:
	make clean
	@rm -f $(NAME) $(wildcard *.out)
	@rm -f $(NAME) $(wildcard *.swo) $(wildcard *.swx) $(wildcard *.swp)
	@rm -f $(NAME) $(wildcard .*.swo) $(wildcard .*.swx) $(wildcard .*.swp)
	@rm -f $(wildcard *.nfs*) $(wildcard .*.nfs*)


re:
	make fclean
	make all

.PHONY: all clean fclean re
