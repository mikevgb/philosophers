/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_tuned.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:59:39 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/12 18:56:36 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_value(char const *str)
{
	while (*str != 0)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

int	ft_atoi(char const *str)
{
	int					base;
	long unsigned int	res;
	int					sign;
	int					i;

	base = 10;
	sign = 1;
	res = 0;
	i = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' && str++)
		sign = -1;
	else if (*str == '+')
		str++;
	while (!check_value(str))
		ft_put_error("Bad input");
	while (ft_isdigit(*str))
		res = (res * base) + (*str++ - 48);
	if (res < 2147483648)
		return ((int)res * sign);
	ft_put_error("Bad input");
	return (0);
}
