/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:32:47 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/29 20:14:08 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* important: data->sem_tp = NULL; 
because we initialise it only later in child processes
so we might not get there */
int	data_init(t_data *data, int n)
{
	if (NULL == data)
		return (unpr_print_error(1, "in data_init: data is NULL"));
	data->n = n;
	data->nate = 0;
	data->stop = 0;
	if (ft_strlen("/sem_forks") != ft_strlcpy(data->sem_forks_name, \
				"/sem_forks", 1 + ft_strlen("/sem_forks")))
		printf("Problem copying name of forks' semaphor");
	ft_strlcpy(data->sem_stdout_name, "/sem_stdout", 20);
	ft_strlcpy(data->sem_ate_enough_name, "/sem_ate_enough", 20);
	ft_strlcpy(data->sem_tp_name, "/sem_tp", 50);
	ft_strlcpy(data->sem_nate_name, "/sem_nate", 50);
	ft_strlcpy(data->sem_stop_name, "/sem_stop", 50);
	ft_strlcpy(data->sem_last_log_name, "/sem_last_log", 20);
	data->sem_forks = NULL;
	data->sem_stdout = NULL;
	data->sem_ate_enough = NULL;
	data->sem_tp = NULL;
	data->sem_nate = NULL;
	data->sem_stop = NULL;
	data->sem_last_log = NULL;
	if (0 != data_start_semaphores(data))
		return (print_error(2, "problem opening semaphors2", data));
	gettimeofday(&data->tp_start, NULL);
	return (0);
}

int	data_start_semaphores(t_data *data)
{
	sem_unlink(data->sem_forks_name);
	data->sem_forks = sem_open(data->sem_forks_name, O_CREAT | O_EXCL, 0644, \
			data->n);
	sem_unlink(data->sem_stdout_name);
	data->sem_stdout = sem_open(data->sem_stdout_name, \
				O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(data->sem_ate_enough_name);
	data->sem_ate_enough = sem_open(data->sem_ate_enough_name, \
		O_CREAT | O_EXCL, 0644, data->n);
	sem_unlink(data->sem_last_log_name);
	data->sem_last_log = sem_open(data->sem_last_log_name, \
				O_CREAT | O_EXCL, 0644, 1);
	if (NULL == data->sem_forks || NULL == data->sem_stdout || \
		NULL == data->sem_ate_enough || NULL == data->sem_last_log)
	{
		close_and_unlink_semaphores(data);
		return (print_error(2, "problem opening semaphors1", data));
	}
	return (0);
}

void	close_one_semaphore(sem_t **sem)
{
	if (NULL == sem || NULL == *sem)
		return ;
	sem_close(*sem);
	*sem = NULL;
	return ;
}

void	close_and_unlink_semaphores(t_data *data)
{
	if (NULL == data)
		return ;
	close_one_semaphore(&data->sem_forks);
	close_one_semaphore(&data->sem_stdout);
	close_one_semaphore(&data->sem_ate_enough);
	close_one_semaphore(&data->sem_tp);
	close_one_semaphore(&data->sem_nate);
	close_one_semaphore(&data->sem_stop);
	close_one_semaphore(&data->sem_last_log);
	sem_unlink(data->sem_forks_name);
	sem_unlink(data->sem_stdout_name);
	sem_unlink(data->sem_ate_enough_name);
	sem_unlink(data->sem_tp_name);
	sem_unlink(data->sem_nate_name);
	sem_unlink(data->sem_stop_name);
	sem_unlink(data->sem_last_log_name);
	return ;
}
