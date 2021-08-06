/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:22:53 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/06 20:58:59 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_threads(t_values **val)
{
	int i;
	pthread_mutex_t **t_knife;

	i = 0;
	t_knife = (pthread_mutex_t**)malloc(sizeof(pthread_mutex_t*) * (*val)->utils.n_philos);
	while(i < (*val)->utils.n_philos)
	{
		val[i]->odd_or_even = i % 2;
		// val[i]->death_flag = 0;
		val[i]->knife = t_knife;
		val[i]->philos = malloc(sizeof(pthread_t));
		val[i]->index = i;
		val[i]->knife[i] = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(val[i]->knife[i], NULL);
		singer_mutex(val[i]);
		death_mutex(val[i]);	
		i++;
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

void	death_mutex(t_values *values)
{
	static pthread_mutex_t death;

	pthread_mutex_init(&death, NULL);
	values->utils.death = &death;
}