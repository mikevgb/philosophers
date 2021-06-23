/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:13:06 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/23 21:50:32 by mvillaes         ###   ########.fr       */
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
	int		forks;
	float	left;
	float	right;
}	t_data;

pthread_mutex_t	lock;
struct timeval start, end;
// pthread_t	*newthread;

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
}

void	*sleep_philo(int i)
{
	// int x;

	// x = 0;
	// while (x < 3)
	// {
		gettimeofday(&start, NULL);
		ft_sleep(2000);
		gettimeofday(&end, NULL);
		printf("TM %ld philo %i is Sleeping\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), i);
	// }
	return (NULL);
}

void	*eat(int i)
{
	
	// int x;

	// x = 0;
	pthread_mutex_lock(&lock);
	// while (x < 3)
	// {
		gettimeofday(&start, NULL);
		ft_sleep(2000);
		gettimeofday(&end, NULL);
		printf("TM %ld philo %i is Eating\n", ((end.tv_sec * 1000 + end.tv_usec) - (start.tv_sec * 1000 + start.tv_usec)), i);
		// x++;
	// }
	pthread_mutex_unlock(&lock);
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
	int *i;

	i = arg;
	// pthread_mutex_t	lock;
	// pthread_mutex_init(&lock, NULL);
	while (1)
	{
		// pthread_mutex_lock(&lock);
		think(*i);
		eat(*i);
		// pthread_mutex_unlock(&lock);
		sleep_philo(*i);
		
		
		// think(i, think_time);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	*newthread;
	t_data		data;
	int			i;
	int			eat_time;
	int			*philos;

	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("\n mutex init failed\n");
		return (1);
	}
	
	i = 0;
	while (i < data.n_philos)
	{
		pthread_mutex_init(&lock[i], NULL);
		i++;
	}
	eat_time = 5;
	data.n_philos = 4;
	newthread = (pthread_t*)malloc(sizeof(newthread) * data.n_philos);
	philos = malloc(sizeof(data.n_philos));
	i = 0;
	while(i < data.n_philos)
	{
		philos[i] = i;
		i++;
	}
	i = 0;
	while (i < data.n_philos)
	{
		pthread_create(&newthread[i], NULL, philo, &philos[i]);
		i++;
	}
	// pthread_create(&newthread[data.n_philos - 1], NULL, philo, &philos[i]);
	i = 0;
	while(i < data.n_philos)
	{
		pthread_join(newthread[i], NULL);
		i++;
	}
	
	// pthread_join(newthread[1], NULL);
	pthread_mutex_destroy(&lock);
	// printf("threads done: *result=%d\n", *result);
	pthread_detach(*newthread);
	// free (newthread);
	// pthread_mutex_destroy(&lock);
	return (0);
}
