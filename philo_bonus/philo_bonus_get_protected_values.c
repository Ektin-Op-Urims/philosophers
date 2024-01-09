/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_get_protected_values1.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:11:24 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 03:27:32 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_nate(t_data *data)
{
	int	nate_tmp;

	if (NULL == data)
		return (-1);
	sem_wait(data->sem_nate);
	nate_tmp = data->nate;
	sem_post(data->sem_nate);
	return (nate_tmp);
}

void	increase_nate(t_data *data)
{
	if (NULL == data)
		return ;
	sem_wait(data->sem_nate);
	++data->nate;
	sem_post(data->sem_nate);
	return ;
}

int	get_stop(t_data *data)
{
	int	stop_tmp;

	if (NULL == data)
		return (-1);
	sem_wait(data->sem_stop);
	stop_tmp = data->stop;
	sem_post(data->sem_stop);
	return (stop_tmp);
}

void	set_stop(t_data *data)
{
	if (NULL == data)
		return ;
	sem_wait(data->sem_stop);
	data->stop = 1;
	sem_post(data->sem_stop);
	return ;
}
