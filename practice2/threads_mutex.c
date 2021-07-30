/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:22:53 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/30 17:28:21 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	fork_mutex(t_values *values)
// {
// 	values->knife = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
// 	pthread_mutex_init(values->knife, NULL);
// }

void	death_thread(t_values *values)
{
	values->death = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_create(values->death, NULL, death, (void *)&values);
}

void	philo_threads(t_values **val)
{
	int i;
	pthread_mutex_t **t_knife;
	// int err;
	// t_values *val;

	i = 0;
	// val = malloc(sizeof(t_values));
	// val->philos = (pthread_t**)malloc(sizeof(pthread_t*) * val->utils.n_philos);
	t_knife = (pthread_mutex_t**)malloc(sizeof(pthread_mutex_t*) * (*val)->utils.n_philos);
	// values->knife = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * values->utils.n_philos);
	// values->death = (pthread_t*)malloc(sizeof(pthread_t));
	// death_thread(values);	
	while(i < (*val)->utils.n_philos)
	{
		// bzero(&val[i], sizeof(t_values));
    	// if (pthread_mutex_init(val[i].knife, NULL) != 0)
    	// {
		// 	printf("\n mutex [%i] init failed\n", i);
		// 	exit (1);
		// }
		// val->philos[i] = malloc(sizeof(pthread_t));
		val[i]->utils.t_eat = 150 * 1000;
		val[i]->utils.t_sleep = 150 * 1000;
		val[i]->utils.t_die = 290 * 1000;
		val[i]->utils.m_eat = 2000000;
		val[i]->odd_or_even = i % 2;
		// val[i].utils.n_philos = values->utils.n_philos;
		val[i]->knife = t_knife;
		val[i]->philos = malloc(sizeof(pthread_t));
		
		// val[i].index = i;
		// fork_mutex(&val[i]);
		val[i]->index = i;
		val[i]->knife[i] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(val[i]->knife[i], NULL);
		singer_mutex(val[i]);
		// death_thread(&val[i]);			
		i++;
		// if (err = pthread_create(&values->philos[i++], NULL, loop, &val[i]) != 0)
		// 	printf("Error creating thread\n");
	}
	i = 0;
	while (i < (*val)->utils.n_philos)
	{
		pthread_create(val[i]->philos, NULL, loop, (void *)val[i]);
		i++;
	}
			
}

void	join_threads(t_values **values)
{
	int i;

	i = 0;
	while(i < (*values)->utils.n_philos)
	{
		pthread_join(values[i]->philos[i], NULL);
		i++;
	}
}

void	singer_mutex(t_values *values)
{
	static pthread_mutex_t print;

	pthread_mutex_init(&print, NULL);
	values->utils.print = &print;
}