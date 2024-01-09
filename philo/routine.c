/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:13:28 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/27 13:48:56 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *data)
{
	t_inda	*inda;

	if (NULL == data)
		return (NULL);
	inda = (t_inda *)data;
	if (inda->coda->n >= 2)
		return (even_subroutine(inda));
	if (1 == inda->coda->n)
		return (one_subroutine(inda));
	return (NULL);
}

void	*even_subroutine(t_inda *inda)
{
	int	s1;
	int	s2;

	if (NULL == inda)
		return (NULL);
	while (0 == check_if_died(inda) && get_bene(inda) && inda->coda->n > 1)
	{
		if (3 == inda->coda->n && 0 == inda->i)
			pthread_mutex_lock(&inda->coda->mutex[2]);
		if (inda->i % 2 == 0)
		{
			usleep(5000);
			s1 = lock_fork_even(inda, "left");
			s2 = lock_fork_even(inda, "right");
		}
		else if (inda->i % 2 == 1)
		{
			usleep(10);
			s1 = lock_fork_even(inda, "right");
			s2 = lock_fork_even(inda, "left");
		}
		do_eat_sleep_think(inda, s1, s2);
	}
	return (NULL);
}

void	do_eat_sleep_think(t_inda *inda, int s1, int s2)
{
	if ((0 != s1 || 0 != s2) && 0 <= unlock_even(inda, s1, s2))
		return ;
	print_state(inda, "is eating");
	copy_time_in_inda(inda);
	usleep(inda->coda->teat * 1000);
	unlock_even(inda, s1, s2);
	++inda->neat;
	if (inda->coda->neat > 0 && inda->neat == inda->coda->neat)
	{
		decrease_bene(inda);
		if (0 == get_bene(inda) && print_state(inda, "finished meal"))
			return ;
	}
	if (get_bene(inda))
	{
		print_state(inda, "is sleeping");
		usleep(inda->coda->tslp * 1000);
	}
	if (0 == check_if_died(inda) && get_bene(inda))
	{
		print_state(inda, "is thinking");
		usleep(100);
	}
	return ;
}

int	unlock_even(t_inda *inda, int s1, int s2)
{
	if (inda->i % 2 == 0)
	{
		if (0 == s2)
			pthread_mutex_unlock(\
				&inda->coda->mutex[(inda->i + 1) % inda->coda->n]);
		if (0 == s1)
			pthread_mutex_unlock(&inda->coda->mutex[inda->i]);
	}
	else if (inda->i % 2 == 1)
	{
		if (0 == s2)
			pthread_mutex_unlock(&inda->coda->mutex[inda->i]);
		if (0 == s1)
			pthread_mutex_unlock(&inda->coda->mutex[\
					(inda->i + 1) % inda->coda->n]);
	}
	if (3 == inda->coda->n && 0 == inda->i)
	{
		pthread_mutex_unlock(&inda->coda->mutex[2]);
	}
	return (0);
}

int	lock_fork_even(t_inda *inda, char const *fork)
{
	if (NULL == inda || NULL == fork)
		return (-1);
	if (0 != check_if_died(inda))
		return (-2);
	if (ft_strncmp("left", fork, ft_strlen("left") + 1) == 0)
	{
		pthread_mutex_lock(&inda->coda->mutex[inda->i]);
	}
	else if (ft_strncmp("right", fork, ft_strlen("right") + 1) == 0)
	{
		pthread_mutex_lock(&inda->coda->mutex[(inda->i + 1) % inda->coda->n]);
	}
	else
		return (-3);
	print_state(inda, "has taken a fork");
	return (0);
}
