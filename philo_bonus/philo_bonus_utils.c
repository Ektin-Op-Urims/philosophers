/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ektin Op Urims <marvin@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:38:11 by Ektin Op Urims    #+#    #+#             */
/*   Updated: 2023/10/29 20:13:14 by Ektin Op Urims   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	ft_strlcpy(char *dst, const char *src, int size)
{
	int	i;
	int	res;

	if (!dst || !src || size <= 0)
		return (-1);
	res = ft_strlen(src);
	i = -1;
	while (++i + 1 < size && src[i])
	{
		dst[i] = src[i];
	}
	dst[i] = '\0';
	return (res);
}

char	*append_num_to_str(char *str, int n)
{
	int	len;
	int	curr_digit;
	int	sign;

	len = ft_strlen(str);
	sign = 1;
	if (n < 0)
		sign = -1;
	while (0 != n)
	{
		curr_digit = n % 10;
		if (curr_digit < 0)
			curr_digit *= -1;
		str[len++] = curr_digit + '0';
		str[len] = '\0';
		n /= 10;
	}
	if (-1 == sign)
	{
		str[len++] = '_';
		str[len] = '\0';
	}
	return (str);
}
