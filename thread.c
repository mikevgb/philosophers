/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 17:53:13 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/18 20:12:57 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_create(t_data *data)
{
	int			i;
	int			*philo_num;
	int			*forks;
	pthread_t	philos;


	philos = alloc_philos(data);
	philo_num = alloc_philos(data);
	forks = alloc_philos(data);
	i = 0;
	while (i < data->n_philos)
	{
		philo_num[i] = i;
		i++;
	}
	i = 0;
	while (i < data->n_philos)
	{
		forks[i] = 0;
		i++;
	}
	i = 0;
	while (i < data->n_philos - 1)
	{
		pthread_create(&philos[i], NULL, philo_do, (void *) &philo_num[i]);
		i++;
	}
	pthread_create(&philos[i - 1], NULL, philo_do, (void *) &philo_num[i - 1]);
	i = 0;
	while (i < data->n_philos)
	{
		pthread_join(&philos[i], NULL);
		i++;
	}
}
