/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:32:47 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/29 15:23:47 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	read_input(int argc, char *argv[], t_data *data)
{
	if (5 != argc && 6 != argc)
		return (unpr_print_error(1, "wrong number of arguments"));
	if (NULL == data)
		return (unpr_print_error(2, "in read_input: data is NULL"));
	data->n = ft_atoi(argv[1]);
	data->tdie = ft_atoi(argv[2]);
	data->teat = ft_atoi(argv[3]);
	data->tslp = ft_atoi(argv[4]);
	if (data->n < 0 || data->tdie < 0 || data->teat < 0 || data->tslp < 0)
		return (unpr_print_error(3, "this number cannot be negative"));
	if (6 == argc)
	{
		data->neat = ft_atoi(argv[5]);
		if (data->neat < 0)
			return (unpr_print_error(4, "neat cannot be negative"));
	}
	else
		data->neat = -1;
	if (0 != data_init(data, data->n))
		return (print_error(5, "Problem initialising data", data));
	return (0);
}

int	unpr_print_error(int res, char const *msg)
{
	printf("%s[%s]%s\n", RED, msg, RES);
	return (res);
}

int	print_error(int res, char const *msg, t_data *data)
{
	if (NULL == data)
		return (-1);
	sem_wait(data->sem_stdout);
	printf("%s[%s]%s\n", RED, msg, RES);
	sem_post(data->sem_stdout);
	return (res);
}

void	copy_time_in_data(t_data *data)
{
	if (NULL == data)
		return ;
	sem_wait(data->sem_tp);
	data->tp_prev.tv_sec = data->tp_now.tv_sec;
	data->tp_prev.tv_usec = data->tp_now.tv_usec;
	sem_post(data->sem_tp);
	return ;
}

void	copy_time_in_data_init(t_data *data)
{
	if (NULL == data)
		return ;
	sem_wait(data->sem_tp);
	data->tp_prev.tv_sec = data->tp_start.tv_sec;
	data->tp_prev.tv_usec = data->tp_start.tv_usec;
	sem_post(data->sem_tp);
	return ;
}
