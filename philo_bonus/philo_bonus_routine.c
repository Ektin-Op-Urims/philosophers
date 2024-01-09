/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:14:49 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 08:03:58 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *data_ptr)
{
	t_data	*data;

	if (NULL == data_ptr)
		return (NULL);
	data = data_ptr;
	if (data->i % 2 == 0)
		usleep(50000);
	while (0 == get_stop(data))
	{
		do_subroutine(data);
	}
	return (NULL);
}

void	do_subroutine(t_data *data)
{
	if (NULL == data)
		return ;
	sem_wait(data->sem_forks);
	print_state(data, "has taken a fork");
	sem_wait(data->sem_forks);
	print_state(data, "has taken a fork");
	print_state(data, "is eating");
	copy_time_in_data(data);
	usleep(data->teat * 1000);
	increase_nate(data);
	sem_post(data->sem_forks);
	sem_post(data->sem_forks);
	if (data->neat != -1 && get_nate(data) == data->neat)
	{
		sem_wait(data->sem_ate_enough);
		print_about_successful_philo(data);
	}
	usleep(500);
	print_state(data, "is sleeping");
	usleep(data->tslp * 1000);
	print_state(data, "is thinking");
	usleep(1000);
	return ;
}

void	print_about_successful_philo(t_data *data)
{
	if (NULL == data)
		return ;
	if (DEBUG_OPT >> 1 & 1)
	{
		sem_wait(data->sem_stdout);
		printf("%s[%d] just ate enough%s\n", LBL, 1 + data->i, RES);
		sem_post(data->sem_stdout);
	}
}

int	print_state(t_data *data, char const *msg)
{
	if (NULL == data)
		return (1);
	sem_wait(data->sem_stdout);
	if (0 == ft_strncmp("is eating", msg, ft_strlen(msg) + 1))
		printf("%s", GREEN);
	else if (0 == ft_strncmp("died", msg, ft_strlen(msg) + 1))
		printf("%s", RED);
	print_timestamp(data);
	if (DEBUG_OPT & 1)
	{
		printf("[%d](%d) [%s]%s\n", data->i + 1, get_nate(data), msg, RES);
	}
	else
	{
		printf("%3d %s%s\n", data->i + 1, msg, RES);
	}
	if (0 != ft_strncmp("died", msg, ft_strlen(msg) + 1))
	{
		sem_post(data->sem_stdout);
	}
	return (0);
}

// should be called within protected stdout
void	print_timestamp(t_data *data)
{
	long unsigned int	time_elapsed;
	long unsigned int	time_elapsed_since_last_time;

	sem_wait(data->sem_tp);
	gettimeofday(&data->tp_now, NULL);
	time_elapsed_since_last_time = \
		(data->tp_now.tv_sec - data->tp_prev.tv_sec) * 1000000 + \
			(data->tp_now.tv_usec - data->tp_prev.tv_usec);
	time_elapsed = \
		(data->tp_now.tv_sec - data->tp_start.tv_sec) * 1000000 + \
			(data->tp_now.tv_usec - data->tp_start.tv_usec);
	sem_post(data->sem_tp);
	if (DEBUG_OPT & 1)
	{
		printf("[%9ld.%03ld] : [%5ld.%03ld] ", \
		time_elapsed / 1000, time_elapsed - time_elapsed / 1000 * 1000, \
		time_elapsed_since_last_time / 1000, \
		time_elapsed_since_last_time - time_elapsed_since_last_time / \
		1000 * 1000);
	}
	else
		printf("%9ld.%03ld ", time_elapsed / 1000, \
			time_elapsed - time_elapsed / 1000 * 1000);
	return ;
}
