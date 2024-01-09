/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_do_work.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:17:18 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 08:14:08 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	do_simulations(t_data *data)
{
	int		i;
	int		*child;

	if (NULL == data || 0 != allocate_for_child(&child, data))
		return (unpr_print_error(1, "in do_sims: data is NULL or malloc"));
	print_header();
	i = -1;
	while (++i < data->n)
	{
		child[i] = fork();
		if (-1 == child[i])
			print_error(3, "problem with fork", data);
		if (0 == child[i])
		{
			if (0 != append_init_data_start_thread(data, i, &child))
				return (3);
			routine(data);
			pthread_join(data->mntr_death_thrd, NULL);
			free_child_close_unlink_sem(&child, data);
			return (0);
		}
	}
	start_ate_monitor(data, &(child[data->n]));
	wait_for_children(data, child);
	return (free_child_close_unlink_sem(&child, data));
}

int	append_init_data_start_thread(t_data *data, int i, int **child)
{
	if (NULL == data)
		return (1);
	data->i = i;
	append_num_to_str(data->sem_tp_name, data->i + 1);
	sem_unlink(data->sem_tp_name);
	data->sem_tp = sem_open(data->sem_tp_name, O_CREAT | O_EXCL, 0644, 1);
	append_num_to_str(data->sem_nate_name, data->i + 1);
	sem_unlink(data->sem_nate_name);
	data->sem_nate = sem_open(data->sem_nate_name, O_CREAT | O_EXCL, 0644, 1);
	sem_unlink(append_num_to_str(data->sem_stop_name, data->i + 1));
	data->sem_stop = sem_open(data->sem_stop_name, O_CREAT | O_EXCL, 0644, 1);
	if (NULL == data->sem_tp || NULL == data->sem_nate)
	{
		print_error(2, "sem_tp or sem_nate failed", data);
		close_and_unlink_semaphores(data);
		free_child_close_unlink_sem(child, data);
		return (2);
	}
	copy_time_in_data_init(data);
	if (0 != pthread_create(&data->mntr_death_thrd, NULL, &do_mntr_death, data))
		return (print_error(4, "problem with monitor death thread", data));
	return (0);
}

int	allocate_for_child(int **child, t_data *data)
{
	if (NULL == child || NULL == data)
		return (unpr_print_error(1, "in allocate_for_child: NULL pointer"));
	*child = (int *)malloc(sizeof(int) * (data->n + 1));
	if (NULL == *child)
		return (print_error(2, "in do_simulations: malloc failed", data));
	(*child)[data->n] = -1;
	return (0);
}

int	free_child_close_unlink_sem(int **child, t_data *data)
{
	if (NULL != child)
	{
		free(*child);
		*child = NULL;
	}
	if (NULL != data)
		close_and_unlink_semaphores(data);
	return (0);
}

void	wait_for_children(t_data *data, int *child)
{
	int	wstatus;
	int	res_child;
	int	i;

	if (NULL == data || NULL == child)
		return ;
	while (1)
	{
		res_child = waitpid(-1, &wstatus, 0);
		if ((-1 == res_child && ECHILD == errno) || (-1 == res_child))
			break ;
		i = -1;
		while (++i < data->n)
			if (res_child != child[i])
				kill(child[i], SIGKILL);
		if (-1 != data->neat && child[data->n] > 0 && child[data->n] > 1000)
			kill(child[data->n], SIGKILL);
		do_some_post_processing(data);
	}
	not_needed_display_all_children(data, child);
	return ;
}
