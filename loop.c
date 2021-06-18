/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:39:53 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/18 21:36:47 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	loop(t_data *data)
{
	int				i;
	int				*philo_num;
	pthread_t		philos;
	pthread_mutex_t	forks;

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

void	think(t_data *data)
{
	usleep(data->)
}

/*
** Semaphores solution
*/

void	philo_loop(int i, t_data *data)
{
	while (1)
	{
		think(data);
		take_forks(i);
		eat();
		put_forks(i);
	}
}

void	take_forks(int i)
{
	lock(&mutex);
	state[i] = THINKING;
	test[i];
	unlock(&mutex);
	down(&s[i]);
}

void	put_forks(int i, t_data *data)
{
	lock(&mutex);
	state[i] = THINKING;
	test(data->left);
	test(data->right);
	unlock(&mutex);
}

void	test(int i, t_data *data)
{
	if (state[i] == THINKING && \
	state[data->left] != EATING && \
	state[data->right] != EATING)
	{
		state[i] = EATING;
		up (&s[i]);
	}
}