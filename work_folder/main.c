/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:36:19 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/28 19:25:55 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_input(t_data *data)
{
	printf("Number of philos = %i\n", data->n_philos);
	printf("Time 2 die = %i\n", data->t_2_die);
	printf("Time 2 eat = %i\n", data->t_2_eat);
	printf("Time 2 sleep = %i\n", data->t_2_sleep);
	printf("Eat num = %i\n", data->eat_num);
	printf("Total args = %i\n", data->total_arg);
}

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
	//usleep(i * 1000);
}

void	*sleep_philo(int i)
{
	// gettimeofday(&start, NULL);
	printf("philo %i is sleeping\n", i);
	ft_sleep(2000);
	// gettimeofday(&end, NULL);
	// printf("TM %ld philo %i is Sleeping\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), data->forks);
	return (NULL);
}

// void	*take_forks(int i)
// {
// 	if ()
// }

void	*eat(int i)
{
	t_data data;
	
	pthread_mutex_lock(&data.forks[i]);
	printf("philo %i has take fork 1\n", i);
	pthread_mutex_lock(&data.forks[(i + 1) % data.n_philos]);
	printf("philo %i has take fork 2\n", i);
	// gettimeofday(&start, NULL);
	ft_sleep(2000);
	//ft_sleep(data->t_2_eat);
	// gettimeofday(&end, NULL);
	// printf("TM %ld philo %i is Eating\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), data->forks);
	pthread_mutex_unlock(&data.forks[(i + 1) % data.n_philos]);
	printf("philo %i has left fork 2\n", i);
	pthread_mutex_unlock(&data.forks[i]);
	printf("philo %i has left fork 1\n", i);
	return (NULL);
}

void	*think(int i)
{
	// gettimeofday(&start, NULL);
	printf("philo %i is thinking\n", i);
	ft_sleep(2000);
	// gettimeofday(&end, NULL);
	// printf("TM %ld philo %i is Thinking\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), data->forks);
	return (NULL);
}

void	*philo(void *arg)
{
	int *i;

	i = arg;
	// t_data	data;

	// data = *(t_data*)arg;
	// pthread_mutex_lock(data.lock_id);
	// data.uid++;
	// pthread_mutex_unlock(data.lock_id);
	while (1)
	{
		think(*i);
		eat(*i);
		sleep_philo(*i);
	}
	
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_data		data;
	int 		i;

	ft_bzero(&data, sizeof(t_data));
	data.total_arg = argc - 1;
	parse(argv, &data);
	data.forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data.n_philos);
	data.id_forks = (int *)malloc(sizeof(int) * data.n_philos);
	data.id_philos = (int *)malloc(sizeof(int) * data.n_philos);
	i = 0;
	while (i < data.n_philos)
	{
		pthread_mutex_init(&data.forks[i], NULL);
		i++;
	}
	// i = 0;
	// while (i < data.n_philos)
	// {
	// 	pthread_mutex_init(&data.lock_id[i], NULL);
	// 	i++;
	// }
	data.newthread = (pthread_t*)malloc(sizeof(pthread_t) * data.n_philos);
	i = 0;
	while (i < data.n_philos)
	{
		pthread_create(&data.newthread[i], NULL, philo, (void *)(size_t)i);
		i++;
	}
	i = 0;
	while(i < data.n_philos)
	{
		pthread_join(data.newthread[i], NULL);
		i++;
	}
	pthread_mutex_destroy(data.forks);
	pthread_detach(*data.newthread);
	// free (newthread);
	return (0);
}