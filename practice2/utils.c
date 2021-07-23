/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:11:38 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/23 21:04:56 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
}

void	singer(t_values *values, char *str)
{
	chronos(values);
	pthread_mutex_lock(values->utils.print);
	printf("[%llu] Philo %i %s\n",values->time - values->start, values->index, str);
	pthread_mutex_unlock(values->utils.print);
}

void	philo_sleep(t_values *values)
{
	singer(values, "🙈 is sleeping");
	ft_sleep(1500);
}

void	chronos(t_values *values)
{
	gettimeofday(&values->end, NULL);
	values->time = ((values->end.tv_sec) * (uint64_t)1000 + (values->end.tv_usec) / 1000);
}