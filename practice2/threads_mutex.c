/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:22:53 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/24 21:59:37 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	make_mutex(t_values *values)
{
	values->knife = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(values->knife, NULL);
}

void	make_threads(t_values *values)
{
	int i;
	// int err;
	t_values *val;

	i = 0;
	val = malloc(sizeof(t_values) * values->utils.n_philos);
	values->philos = (pthread_t*)malloc(sizeof(pthread_t) * values->utils.n_philos);
	while(i < values->utils.n_philos)
	{
		// bzero(&val[i], sizeof(t_values));

		val[i].utils.t_eat = 200 * 1000;
		val[i].utils.t_sleep = 100 * 1000;
		val[i].utils.t_die = 400;
		val[i].utils.m_eat = 2000000;
		
		val[i].index = i;
		make_mutex(&val[i]);
		singer_mutex(&val[i]);
		pthread_create(&values->philos[i], NULL, loop, (void *)&val[i]);
		i++;
		// if (err = pthread_create(&values->philos[i++], NULL, loop, &val[i]) != 0)
		// 	printf("Error creating thread\n");
	}			
}

void	join_threads(t_values *values)
{
	int i;

	i = 0;
	while(i < values->utils.n_philos)
		pthread_join(values->philos[i++], NULL);
}

void	singer_mutex(t_values *values)
{
	static pthread_mutex_t print;

	pthread_mutex_init(&print, NULL);
	values->utils.print = &print;
}