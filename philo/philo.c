/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:20:58 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/27 15:18:13 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	read_input(int argc, char *argv[], t_coda *coda)
{
	if (5 != argc && 6 != argc)
		return (print_error(1, "wrong number of arguments"));
	if (NULL == coda)
		return (print_error(2, "in read_input: coda is NULL"));
	coda->n = ft_atoi(argv[1]);
	coda->tdie = ft_atoi(argv[2]);
	coda->teat = ft_atoi(argv[3]);
	coda->tslp = ft_atoi(argv[4]);
	if (coda->n <= 0 || coda->tdie <= 0 || coda->teat <= 0 || coda->tslp <= 0)
		return (print_error(3, "this number cannot be negative"));
	if (6 == argc)
	{
		coda->neat = ft_atoi(argv[5]);
		if (coda->neat < 0)
			return (print_error(4, "neat can not be negative"));
	}
	else
		coda->neat = -1;
	if (0 != coda_init(coda, coda->n))
		return (print_error(5, "Problem initialising coda"));
	return (0);
}

int	do_simulations(t_coda *coda)
{
	pthread_t	*t;
	pthread_t	monitor_thread;
	t_inda		*inda;
	int			i;

	if (NULL == coda)
		return (print_error(1, "in do_simulations: coda is NULL"));
	t = (pthread_t *)malloc(sizeof(pthread_t) * coda->n);
	if (NULL == t)
		return (print_error(2, "cannot allocate memory for threads"));
	inda = (t_inda *)malloc(sizeof(t_inda) * coda->n);
	if (NULL == inda)
		return (print_error(3, "cannot allocate memory for inda"));
	print_header();
	starting_threads(inda, coda, t);
	if (0 != pthread_create(&monitor_thread, NULL, &monitor, inda))
		print_error(5, "monitor thread failed to start");
	i = -1;
	while (++i < coda->n)
		pthread_join(t[i], NULL);
	pthread_join(monitor_thread, NULL);
	clear_simulations(&t, &inda);
	return (0);
}

void	starting_threads(t_inda *inda, t_coda *coda, pthread_t *t)
{
	int	i;

	if (NULL == inda || NULL == coda || NULL == t)
	{
		print_error(1, "in starting_threads: NULL pointer");
		return ;
	}
	i = -1;
	while (++i < coda->n)
	{
		inda_init(&inda[i], coda, i);
		if (0 != pthread_create(&t[i], NULL, &routine, &inda[i]))
			print_error(4, "problem starting thread");
	}
	return ;
}

void	clear_simulations(pthread_t **t, t_inda **inda)
{
	if (NULL != t && NULL != *t)
	{
		free(*t);
		*t = NULL;
	}
	if (NULL != inda && NULL != *inda)
	{
		pthread_mutex_destroy(&((*inda)->mutex_time));
		free(*inda);
		*inda = NULL;
	}
	return ;
}

int	main(int argc, char *argv[])
{
	t_coda	coda;
	int		res;

	res = read_input(argc, argv, &coda);
	if (0 != res)
	{
		return (print_error(1, "Something is wrong"));
	}
	res = do_simulations(&coda);
	coda_release(&coda);
	return (res);
}
