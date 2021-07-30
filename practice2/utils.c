/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:11:38 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/30 16:56:32 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	singer(t_values *val, char *str)
{
	
	// death(val);
	chronos(val);
	pthread_mutex_lock(*(&val->utils.print));
	
	printf("[%04llu] %i %s\n",val->time - val->start, val->index, str);
	// printf("[%04llu] %i %llu <-last meal %i N_philos\n",val->time - val->start, val->index + 1, val->last_meal - val->start, val->utils.n_philos);
	pthread_mutex_unlock(*(&val->utils.print));
}

void	philo_sleep(t_values *val)
{
	singer(val, "🙈 is sleeping");
	usleep(val->utils.t_sleep);
}

void	chronos(t_values *val)
{
	gettimeofday(&val->end, NULL);
	val->time = ((val->end.tv_sec) * (uint64_t)1000 + (val->end.tv_usec) / 1000);
}

void	parse(char **argv, t_values *val)
{
	// if (val->t_arg < 4)
	// 	ft_put_error("Missing arguments");
	// if (val->t_arg > 5)
	// 	ft_put_error("Too many arguments");
	val->utils.n_philos = ft_atoi(argv[1]);
	// val->utils.t_die = ft_atoi(argv[2]);
	// val->utils.t_eat = ft_atoi(argv[3]);
	// val->utils.t_sleep = ft_atoi(argv[4]);
	// if (val->t_arg > 4)
	// 	val->utils.m_eat = ft_atoi(argv[5]);
}