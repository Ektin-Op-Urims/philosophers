/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:51:23 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/23 16:10:24 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int res, char const *msg)
{
	printf("%s[%s]%s\n", RED, msg, RES);
	return (res);
}

void	copy_time_in_inda(t_inda *inda)
{
	if (NULL == inda)
		return ;
	pthread_mutex_lock(&inda->mutex_time);
	inda->tp_prev.tv_sec = inda->tp_now.tv_sec;
	inda->tp_prev.tv_usec = inda->tp_now.tv_usec;
	pthread_mutex_unlock(&inda->mutex_time);
	return ;
}

int	ft_atoi(char const *str)
{
	int	res;
	int	sign;

	if (NULL == str)
		return (0);
	res = 0;
	while (' ' == *str || ('\t' <= *str && '\r' >= *str))
		++str;
	sign = 1;
	if ('-' == *str)
	{
		sign = -1;
		++str;
	}
	else if ('+' == *str)
		++str;
	while ('\0' != *str && *str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		++str;
	}
	return (sign * res);
}

int	ft_strlen(char const *str)
{
	int	len;

	if (NULL == str)
		return (0);
	len = 0;
	while (*str++)
		++len;
	return (len);
}

int	ft_strncmp(char const *str1, char const *str2, int n)
{
	int	res;
	int	i;

	if (NULL == str1 || NULL == str2)
	{
		if (NULL == str1 && NULL == str2)
			return (0);
		return (1);
	}
	if (n <= 0)
		return (0);
	i = -1;
	while (++i < n && str1[i] && str2[i])
	{
		res = str1[i] - str2[i];
		if (0 != res)
			return (res);
	}
	if (i == n)
		return (0);
	return (str1[i] - str2[i]);
}
