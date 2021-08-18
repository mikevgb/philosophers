/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:48:17 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/17 19:49:13 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_put_error(char *str)
{
	write(2, "Error: ", 8);
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	exit (1);
}
