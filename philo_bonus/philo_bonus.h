/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:21:41 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 08:27:09 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>     // printf
# include <stdlib.h>    // malloc
# include <unistd.h>    // usleep, sleep
# include <sys/time.h>  // gettimeofday
# include <pthread.h>
# include <semaphore.h> // sem_wait, sem_post
# include <fcntl.h>     // sem_open, sem_close
# include <sys/wait.h>  // waitpid
# include <errno.h>     // errno, ECHILD: 
//			while (-1 != wait(NULL) || errno != ECHILD)

# define RED "\033[31m"
# define YEL "\033[33m"
# define BLU "\033[34m"
# define PUR "\033[35m"
# define LBL "\033[36m"
# define GRE "\033[37m"
# define GREEN "\033[32m"
# define RES "\033[0m"

# ifndef DEBUG_OPT
#  define DEBUG_OPT 1
# endif

typedef struct s_data
{
	int				n;
	int				i;
	int				tdie;
	int				teat;
	int				tslp;
	int				neat;
	int				nate;
	sem_t			*sem_forks;
	sem_t			*sem_stdout;
	sem_t			*sem_ate_enough;
	sem_t			*sem_tp;
	sem_t			*sem_nate;
	int				stop;
	sem_t			*sem_stop;
	pthread_t		routine_thread;
	pthread_t		mntr_death_thrd;
	pthread_t		mntr_ate_boss_t;
	pthread_t		mntr_ate_work_t;
	char			sem_forks_name[20];
	char			sem_stdout_name[20];
	char			sem_ate_enough_name[20];
	char			sem_tp_name[50];
	char			sem_nate_name[50];
	char			sem_stop_name[50];
	struct timeval	tp_start;
	struct timeval	tp_prev;
	struct timeval	tp_now;
	struct timeval	tp_last_log;
	sem_t			*sem_last_log;
	char			sem_last_log_name[20];
}	t_data;

// philo_bonus_utils.c
int		ft_atoi(char const *str);
int		ft_strlen(char const *str);
int		ft_strncmp(char const *str1, char const *str2, int n);
int		ft_strlcpy(char *dst, const char *src, int size);
char	*append_num_to_str(char *str, int n);

// philo_bonus_aux.c
int		read_input(int argc, char *argv[], t_data *data);
int		unpr_print_error(int res, char const *msg);
int		print_error(int res, char const *msg, t_data *data);
void	copy_time_in_data(t_data *data);
void	copy_time_in_data_init(t_data *data);

// philo_bonus_data.c
int		data_init(t_data *data, int n);
int		data_start_semaphores(t_data *data);
void	close_one_semaphore(sem_t **sem);
void	close_and_unlink_semaphores(t_data *data);

// philo_bonus_do_work.c
int		do_simulations(t_data *data);
int		append_init_data_start_thread(t_data *data, int i, int **child);
int		allocate_for_child(int **child, t_data *data);
int		free_child_close_unlink_sem(int **child, t_data *data);
void	wait_for_children(t_data *data, int *child);

// philo_bonus_do_work_aux.c
void	do_some_post_processing(t_data *data);
void	not_needed_display_all_children(t_data *data, int *child);
void	*mntr_ate_work(void *data);
void	*mntr_ate_boss(void *data);
int		start_ate_monitor(t_data *data, int *child);

// philo_bonus_routine.c
void	*routine(void *data);
void	do_subroutine(t_data *data);
void	print_about_successful_philo(t_data *data);
int		print_state(t_data *data, char const *option);
void	print_timestamp(t_data *data);

// philo_bonus_print_header.c
void	print_header(void);

// philo_bonus_monitor.c
void	*do_mntr_death(void *data);
int		check_if_died(t_data *data);

// philo_bonus_get_protected_values1.c
int		get_nate(t_data *data);
void	increase_nate(t_data *data);
int		get_stop(t_data *data);
void	set_stop(t_data *data);

#endif // PHILO_BONUS_H
