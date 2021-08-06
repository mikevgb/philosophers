/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:11:38 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/06 21:03:07 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	singer(t_values *val, char *str)
{
	// printf("death flag 1 = %i, index %i\n", val->death_flag, val->index);
	if (!val->death_flag)
	{
		chronos(val, 1);
		pthread_mutex_lock(*(&val->utils.print));
		// printf("death flag 2 = %i, index %i\n", val->death_flag, val->index);
		printf("[%04llu] %i %s\n",val->time - val->start, val->index + 1, str);
		pthread_mutex_unlock(*(&val->utils.print));
		pthread_mutex_lock(*(&val->utils.death));
		death(val);
		pthread_mutex_unlock(*(&val->utils.death));
	}
	
	// if (!death(val))
	// 	pthread_mutex_unlock(*(&val->utils.death));
	// else
	// 	return (1);
	// return (0);
}

void	chronos(t_values *val, int flag)
{
	gettimeofday(&val->end, NULL);
	if (!flag)
		val->last_meal = ((((val->end.tv_sec) * (uint64_t)1000 + (val->end.tv_usec) / 1000)));
	else
		val->time = ((((val->end.tv_sec) * (uint64_t)1000 + (val->end.tv_usec) / 1000)) - (val->utils.n_philos * 3));
}
