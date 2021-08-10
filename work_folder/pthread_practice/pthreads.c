/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:13:06 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/28 18:59:44 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
# define THINKING 0;
# define EATING 1;
# define SLEEP 2;

typedef struct s_data
{
	int		n_philos;
	int		t_2_die;
	int		t_2_eat;
	int		t_2_sleep;
	int		eat_num;
	int		total_arg;
	float	left;
	float	right;
	int		*forks;
}	t_data;

// Mutex for the forks array
pthread_mutex_t	fork_mutex = PTHREAD_MUTEX_INITIALIZER;
// Signal that indicates when a fork becomes available
pthread_cond_t fork_available = PTHREAD_COND_INITIALIZER;

struct timeval start, end;

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
}

void	*sleep_philo(int i)
{
	gettimeofday(&start, NULL);
	ft_sleep(2000);
	gettimeofday(&end, NULL);
	printf("TM %ld philo %i is Sleeping\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), i);
	return (NULL);
}

void	*eat(int i)
{
	t_data	data;
	pthread_mutex_lock(&fork_mutex);
	gettimeofday(&start, NULL);
	if (data.forks[i] == 0 || data.forks[(i + 1) % 5] == 0)
	{
		ft_sleep(2000);
		gettimeofday(&end, NULL);
		printf("TM %ld philo %i is Eating\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), i);
	}
	pthread_mutex_unlock(&fork_mutex);
	return (NULL);
}

void	*think(int i)
{
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	printf("TM %ld philo %i is Thinking\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), i);
	return (NULL);
}

void	can_i_eat()
{

}

void	*philo(void *arg)
{
	int i;

	i = *(int *)arg;
	while (1)
	{
		think(i);
		eat(i);
		sleep_philo(i);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	*philos;
	t_data		data;
	int			i;
	int			eat_time;
	// int			*philos;

	if (pthread_mutex_init(&fork_mutex, NULL) != 0)
	{
		printf("\n mutex init failed\n");
		return (1);
	}

	eat_time = 5;
	data.n_philos = 4;
	philos = (pthread_t*)malloc(sizeof(philos) * data.n_philos);
	// philos = malloc(sizeof(data.n_philos));
	data.forks = malloc(sizeof(data.n_philos));
	//initialize forks
	i = 0;
	while (i < data.n_philos)
	{
		data.forks[i] = 0;
		i++;
	}
	// i = 0;
	// while(i < data.n_philos)
	// {
	// 	philos[i] = i;
	// 	i++;
	// }
	i = 0;
	while (i < data.n_philos)
	{
		pthread_create(&philos[i], NULL, &philo, &i);
		i++;
	}
	i = 0;
	while(i < data.n_philos)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&fork_mutex);
	pthread_detach(*philos);
	// free (newthread);
	return (0);
}
