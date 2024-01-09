/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_print_header.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 08:13:07 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/30 08:28:17 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_header(void)
{
	if (!(1 & DEBUG_OPT))
		printf("%sFor a better experience, change DEBUG_OPT to %d\n", \
			RED, DEBUG_OPT + 1);
	if (DEBUG_OPT & 1)
	{
		printf("%sBelow,\n", YEL);
		printf("T - time elapsed since the beginning of simulation.\n");
		printf("t - time elapsed since the beginning of the last meal.\n");
		printf("n - the index number of the philosopher.\n");
		printf("e - how many meals the philosopher already took.\n");
		printf("msg - message\n\n");
		printf("[%13s] : [%9s] [n](e) [%5s]%s\n\n", "T", "t", "msg", RES);
	}
	else
	{
		printf("%sBelow,\n", YEL);
		printf("T - time elapsed since the beginning of simulation.\n");
		printf("n - the index number of the philosopher.\n");
		printf("msg - message\n\n");
		printf("%13s   n %5s%s\n\n", "T", "msg", RES);
	}
}
