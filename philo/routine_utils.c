/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:28 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/28 18:56:57 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_state(t_inda *inda, char const *msg)
{
	if (NULL == inda)
		return (1);
	pthread_mutex_lock(&inda->coda->mutex_stdout);
	if (0 == get_bene(inda) && 1 == bad_news_delivered(inda))
	{
		pthread_mutex_unlock(&inda->coda->mutex_stdout);
		return (2);
	}
	if (0 == get_bene(inda) && 0 == bad_news_delivered(inda) && \
		(0 == ft_strncmp("died", msg, ft_strlen("died") + 1) || \
		0 == ft_strncmp("finished meal", msg, ft_strlen(msg) + 1)))
		deliver_bad_news(inda);
	if (0 == ft_strncmp("is eating", msg, ft_strlen("is eating") + 1))
		printf("%s", GREEN);
	print_timestamp(inda);
	printf("[%d](%d){%d} [%s]%s\n", inda->i + 1, inda->neat, \
		get_bene(inda), msg, RES);
	pthread_mutex_unlock(&inda->coda->mutex_stdout);
	return (3);
}

// should be called from within protected stdout
void	print_timestamp(t_inda *inda)
{
	long unsigned int	time_elapsed;
	long unsigned int	time_elapsed_since_last_time;

	pthread_mutex_lock(&inda->mutex_time);
	gettimeofday(&inda->tp_now, NULL);
	time_elapsed_since_last_time = \
		(inda->tp_now.tv_sec - inda->tp_prev.tv_sec) * 1000000 + \
			(inda->tp_now.tv_usec - inda->tp_prev.tv_usec);
	time_elapsed = \
		(inda->tp_now.tv_sec - inda->coda->tp.tv_sec) * 1000000 + \
			(inda->tp_now.tv_usec - inda->coda->tp.tv_usec);
	pthread_mutex_unlock(&inda->mutex_time);
	printf("[%9ld.%03ld] : [%5ld.%03ld] ", \
		time_elapsed / 1000, time_elapsed - time_elapsed / 1000 * 1000, \
		time_elapsed_since_last_time / 1000, \
		time_elapsed_since_last_time - time_elapsed_since_last_time / \
		1000 * 1000);
	return ;
}

int	check_if_died(t_inda *inda)
{
	if (NULL == inda)
		return (1);
	pthread_mutex_lock(&inda->mutex_time);
	gettimeofday(&inda->tp_now, NULL);
	pthread_mutex_unlock(&inda->mutex_time);
	if (get_time_elapsed(inda) > 1000 * inda->coda->tdie)
	{
		pthread_mutex_lock(&inda->coda->mutex_bene);
		inda->coda->bene = 0;
		pthread_mutex_unlock(&inda->coda->mutex_bene);
		print_state(inda, "died");
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_inda	*inda;
	int		i;

	if (NULL == data)
		return (NULL);
	inda = (t_inda *)data;
	while (get_bene(inda))
	{
		i = -1;
		while (++i < inda->coda->n)
		{
			if (0 != check_if_died(&inda[i]))
				return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}

void	*one_subroutine(t_inda *inda)
{
	if (NULL == inda)
		return (NULL);
	if (1 == inda->coda->n)
	{
		lock_fork_even(inda, "left");
		while (0 == check_if_died(inda))
		{
		}
		pthread_mutex_unlock(&inda->coda->mutex[0]);
	}
	return (NULL);
}
