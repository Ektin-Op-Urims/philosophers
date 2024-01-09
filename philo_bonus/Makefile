# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/27 12:08:42 by Ektin Op Urims    #+#    #+#              #
#    Updated: 2023/10/30 08:14:29 by Ektin Op Urims   ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = philo_bonus.c \
	philo_bonus_utils.c \
	philo_bonus_aux.c \
	philo_bonus_data.c \
	philo_bonus_do_work.c \
	philo_bonus_do_work_aux.c \
	philo_bonus_routine.c \
	philo_bonus_monitor.c \
	philo_bonus_get_protected_values.c \
	philo_bonus_print_header.c \

HEADERS = philo_bonus.h

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

NORM = /bin/norminette

CFLAGS += -Wall -Wextra -Wpedantic -Werror
CFLAGS += -pthread
CFLAGS += -fsanitize=thread -g

CC = gcc

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	make NORM

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
	@rm -f $(NAME) $(wildcard *.nfs*)

re:
	make fclean
	make all
