/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:32:52 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/28 19:02:36 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	coda_init(t_coda *coda, int n)
{
	coda->n = n;
	coda->bene = coda->n;
	coda->print_die = 0;
	if (0 != pthread_mutex_init(&coda->mutex_stdout, NULL))
		return (print_error(1, "problem starting mutex_stdout"));
	if (0 != pthread_mutex_init(&coda->mutex_bene, NULL))
	{
		pthread_mutex_destroy(&coda->mutex_stdout);
		return (print_error(1, "problem starting mutex_bene"));
	}
	coda->mutex = NULL;
	coda->mutex = (pthread_mutex_t *)malloc(coda->n * \
			sizeof(pthread_mutex_t));
	if (NULL == coda->mutex)
		return (print_error(2, "failed malloc in coda_init"));
	if (0 != start_mutex(coda))
		return (print_error(3, "problem starting mutex"));
	gettimeofday(&coda->tp, NULL);
	return (0);
}

int	start_mutex(t_coda *coda)
{
	int	i;
	int	j;

	if (NULL == coda)
		return (print_error(1, "in start_mutex: coda is NULL"));
	i = -1;
	while (++i < coda->n)
	{
		if (0 != pthread_mutex_init(&coda->mutex[i], NULL))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&coda->mutex[j]);
			free(coda->mutex);
			coda->mutex = NULL;
			return (2);
		}
	}
	return (0);
}

int	coda_release(t_coda *coda)
{
	int	i;

	i = -1;
	while (++i < coda->n)
		pthread_mutex_destroy(&coda->mutex[i]);
	free(coda->mutex);
	coda->mutex = NULL;
	pthread_mutex_destroy(&coda->mutex_stdout);
	pthread_mutex_destroy(&coda->mutex_bene);
	return (0);
}

int	inda_init(t_inda *inda, t_coda *coda, int i)
{
	if (NULL == inda)
		return (print_error(1, "passed NULL to inda_init"));
	if (0 != pthread_mutex_init(&inda->mutex_time, NULL))
		return (print_error(2, "problem starting mutex_time"));
	inda->i = i;
	inda->neat = 0;
	inda->coda = coda;
	pthread_mutex_lock(&inda->mutex_time);
	inda->tp_prev.tv_sec = inda->coda->tp.tv_sec;
	inda->tp_prev.tv_usec = inda->coda->tp.tv_usec;
	gettimeofday(&inda->tp_now, NULL);
	pthread_mutex_unlock(&inda->mutex_time);
	return (0);
}

void	print_header(void)
{
	printf("%sBelow,\n", YEL);
	printf("T - time elapsed since the beginning of simulation.\n");
	printf("t - time elapsed since the beginning of the last meal.\n");
	printf("n - the index number of the philosopher.\n");
	printf("e - how many meals the philosopher already took.\n");
	printf("b - number of philosophers minus the number of ");
	printf("philosophers that\n    have already taken needed number ");
	printf("of meals.\n");
	printf("    It is 0 in case everyone already have eaten ");
	printf("or if someone died.\n");
	printf("msg - message\n\n");
	printf("[%13s] : [%9s] [n](e){b} [%5s]%s\n\n", "T", "t", "msg", RES);
}
