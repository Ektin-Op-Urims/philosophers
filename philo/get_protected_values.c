/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_protected_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:18:22 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/28 22:32:14 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_bene(t_inda *inda)
{
	int	bene_tmp;

	if (NULL == inda)
		return (0);
	pthread_mutex_lock(&inda->coda->mutex_bene);
	bene_tmp = inda->coda->bene;
	pthread_mutex_unlock(&inda->coda->mutex_bene);
	return (bene_tmp);
}

void	decrease_bene(t_inda *inda)
{
	if (NULL == inda)
		return ;
	pthread_mutex_lock(&inda->coda->mutex_bene);
	if (inda->coda->bene)
		--inda->coda->bene;
	pthread_mutex_unlock(&inda->coda->mutex_bene);
	return ;
}

t_size	get_time_elapsed(t_inda *inda)
{
	t_size	res;

	pthread_mutex_lock(&inda->mutex_time);
	gettimeofday(&inda->tp_now, NULL);
	res = 1000000 * (inda->tp_now.tv_sec - inda->tp_prev.tv_sec) + \
		(inda->tp_now.tv_usec - inda->tp_prev.tv_usec);
	pthread_mutex_unlock(&inda->mutex_time);
	return (res);
}

void	deliver_bad_news(t_inda *inda)
{
	if (NULL == inda)
		return ;
	pthread_mutex_lock(&inda->coda->mutex_bene);
	inda->coda->print_die = 1;
	pthread_mutex_unlock(&inda->coda->mutex_bene);
	return ;
}

int	bad_news_delivered(t_inda *inda)
{
	int	res;

	if (NULL == inda)
		return (-1);
	pthread_mutex_lock(&inda->coda->mutex_bene);
	res = inda->coda->print_die;
	pthread_mutex_unlock(&inda->coda->mutex_bene);
	return (res);
}
