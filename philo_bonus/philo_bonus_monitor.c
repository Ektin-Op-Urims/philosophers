/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_monitor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:29:15 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/29 20:37:24 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*do_mntr_death(void *data_ptr)
{
	t_data	*data;

	if (NULL == data_ptr)
		return (NULL);
	data = (t_data *)data_ptr;
	while (1)
	{
		if (0 != check_if_died(data))
		{
			set_stop(data);
			exit(1);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

int	check_if_died(t_data *data)
{
	struct timeval	tp_tmp;
	long int		period_of_time;

	if (NULL == data)
		return (1);
	gettimeofday(&tp_tmp, NULL);
	sem_wait(data->sem_tp);
	period_of_time = (tp_tmp.tv_usec - data->tp_prev.tv_usec) + \
		1000000 * (tp_tmp.tv_sec - data->tp_prev.tv_sec);
	sem_post(data->sem_tp);
	if (period_of_time > 1000 * data->tdie)
	{
		print_state(data, "died");
		return (1);
	}
	return (0);
}
