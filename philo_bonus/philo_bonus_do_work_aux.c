/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_do_work_aux.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:55:44 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 07:52:21 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	do_some_post_processing(t_data *data)
{
	if (NULL == data)
		return ;
	sem_post(data->sem_stdout);
	return ;
}

void	not_needed_display_all_children(t_data *data, int *child)
{
	int	i;

	if (NULL == data || NULL == child)
		return ;
	if (DEBUG_OPT >> 1 & 1)
	{
		i = -1;
		while (++i < data->n + 1)
		{
			sem_wait(data->sem_stdout);
			printf("My [%d]th child is [%d]\n", i, child[i]);
			sem_post(data->sem_stdout);
		}
	}
}

void	*mntr_ate_work(void *data_ptr)
{
	t_data	*data;

	if (NULL == data_ptr)
		return (NULL);
	data = data_ptr;
	while (1)
	{
		if (-1 != data->neat)
		{
			sem_wait(data->sem_ate_enough);
			sem_post(data->sem_ate_enough);
			sem_wait(data->sem_last_log);
			gettimeofday(&data->tp_last_log, NULL);
			sem_post(data->sem_last_log);
		}
		usleep(10);
	}
	return (NULL);
}

void	*mntr_ate_boss(void *data_ptr)
{
	t_data			*data;
	struct timeval	tp;
	struct timeval	tp_last_log_tmp;

	if (NULL == data_ptr)
		return (NULL);
	data = data_ptr;
	usleep(50000);
	while (1)
	{
		sem_wait(data->sem_last_log);
		tp_last_log_tmp.tv_sec = data->tp_last_log.tv_sec;
		tp_last_log_tmp.tv_usec = data->tp_last_log.tv_usec;
		sem_post(data->sem_last_log);
		gettimeofday(&tp, NULL);
		if (1000000 * (tp.tv_sec - tp_last_log_tmp.tv_sec) + \
			(tp.tv_usec - tp_last_log_tmp.tv_usec) > 250)
		{
			sem_wait(data->sem_stdout);
			exit(1);
		}
		usleep(100);
	}
	return (NULL);
}

int	start_ate_monitor(t_data *data, int *child_mntr_ate)
{
	if (NULL == data || NULL == child_mntr_ate)
		return (1);
	if (-1 == data->neat)
	{
		*child_mntr_ate = -1;
		return (2);
	}
	*child_mntr_ate = fork();
	if (-1 == *child_mntr_ate)
		return (print_error(4, "problem with ate monitor fork", data));
	if (0 == *child_mntr_ate)
	{
		if (0 != pthread_create(&data->mntr_ate_work_t, NULL, \
						&mntr_ate_work, data))
			print_error(5, "failed start mntr ate work", data);
		if (0 != pthread_create(&data->mntr_ate_boss_t, NULL, \
						&mntr_ate_boss, data))
			print_error(6, "failed start monitor ate boss", data);
		pthread_join(data->mntr_ate_boss_t, NULL);
		pthread_join(data->mntr_ate_work_t, NULL);
		return (0);
	}
	return (0);
}
