/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:21:41 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/28 20:50:27 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>    // printf
# include <stdlib.h>   // malloc
# include <unistd.h>   // usleep, sleep
# include <sys/time.h> // gettimeofday
# include <pthread.h>

# define RED "\033[31m"
# define YEL "\033[33m"
# define BLU "\033[34m"
# define PUR "\033[35m"
# define LBL "\033[36m"
# define GRE "\033[37m"
# define GREEN "\033[32m"
# define RES "\033[0m"

typedef long int	t_size;

typedef struct s_coda
{
	int				n;
	int				tdie;
	int				teat;
	int				tslp;
	int				neat;
	int				bene;
	int				print_die;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_stdout;
	pthread_mutex_t	mutex_bene;
	struct timeval	tp;
}	t_coda;

typedef struct s_inda
{
	int				i;
	int				neat;
	t_coda			*coda;
	struct timeval	tp_prev;
	struct timeval	tp_now;
	pthread_mutex_t	mutex_time;
}	t_inda;

// data.c
int		coda_init(t_coda *coda, int n);
int		start_mutex(t_coda *coda);
int		coda_release(t_coda *coda);
int		inda_init(t_inda *inda, t_coda *coda, int n);
void	print_header(void);

// philo_aux.c
int		print_error(int n, char const *msg);
void	copy_time_in_inda(t_inda *inda);
int		ft_atoi(char const *str);
int		ft_strlen(char const *str);
int		ft_strncmp(char const *str1, char const *str2, int n);

// routine.c
void	*routine(void *data);
void	*even_subroutine(t_inda *inda);
void	do_eat_sleep_think(t_inda *inda, int s1, int s2);
int		unlock_even(t_inda *inda, int s1, int s2);
int		lock_fork_even(t_inda *inda, char const *fork);

// routine_utils.c
int		print_state(t_inda *inda, char const *option);
void	print_timestamp(t_inda *inda);
int		check_if_died(t_inda *inda);
void	*one_subroutine(t_inda *inda);
void	*monitor(void *data);

// philo.c
int		read_input(int argc, char *argv[], t_coda *coda);
int		do_simulations(t_coda *coda);
void	starting_threads(t_inda *inda, t_coda *coda, pthread_t *t);
void	clear_simulations(pthread_t **t, t_inda **inda);

// get_protected_values.c
int		get_bene(t_inda *inda);
void	decrease_bene(t_inda *inda);
t_size	get_time_elapsed(t_inda *inda);
void	deliver_bad_news(t_inda *inda);
int		bad_news_delivered(t_inda *inda);

#endif // PHILO_H
