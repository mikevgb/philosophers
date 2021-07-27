/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/27 22:28:27 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_values *val, int odd_or_even)
{
	val->last_meal = val->time;
	pthread_mutex_lock(*(&val->utils.print));
	printf("[%04llu] %i %llu <-last meal\n",val->time - val->start, val->index + 1, val->last_meal - val->start);
	pthread_mutex_unlock(*(&val->utils.print));
	singer(val, "🥩 is eating");
	usleep(val->utils.t_eat);
	if (!odd_or_even)
	{
		pthread_mutex_unlock(*(&val->knife) + 1 % 5);
		pthread_mutex_unlock(*(&val->knife));
	}	
	else
	{	
		pthread_mutex_unlock(*(&val->knife));
		pthread_mutex_unlock(*(&val->knife) + 1 % 5);
	}
}

void	dirty_eat(t_values *val)
{
	int odd_or_even;

	odd_or_even = val->index % 2;
	if (!odd_or_even)
	{
		pthread_mutex_lock(*(&val->knife));
		pthread_mutex_lock(*(&val->knife) + 1 % 5);
		singer(val, "⚔️  locked knifes");
		eating(val, odd_or_even);
	}
	else
	{
		pthread_mutex_lock(*(&val->knife) + 1 % 5);
		pthread_mutex_lock(*(&val->knife));
		
		singer(val, "⚔️  locked knifes");
		eating(val, odd_or_even);
	}
}

void	*loop(void *s_truct)
{
	t_values *val;
	val = (t_values *)s_truct;
	
	val->time = 0;
	chronos(val);
	val->start = val->time;
	while (1)
	{
		dirty_eat(val);
		philo_sleep(val);
		singer(val, "🤯 is thinking");
	}
	return (NULL);
}

// int		death(t_values *val)
// {
// 	int i;
// 	int x;
// 	uint64_t tmp1;
// 	uint64_t tmp2;

// 	tmp1 = 0;
// 	tmp2 = 0;
// 	i = 0;
// 	x = 0;
// 	val[i].death = val[i].utils.t_die;
	
// 	while (1)
// 	{
// 		tmp2 = (val[i].time - val[i].start) + tmp1;
// 		if (tmp2 > val[i].death)
// 		{
// 			singer(val, "🏴‍☠️ died");
// 			pthread_mutex_destroy(val->knife);
// 			pthread_detach(*val->philos);
// 			break;
// 		}
// 		val[i].death += val[i].time;
// 		tmp1 = val[i].time;
// 		++i;
// 		if (i > val->utils.n_philos)
// 			i = 0;
// 		if (val->utils.m_eat > 0)
// 		{
// 			if (val[i].c_eat > val->utils.m_eat)
// 			{
// 				pthread_detach(*val->philos);
// 				pthread_mutex_destroy(val->knife);
// 				break;
// 			}
// 		}
// 	}
// 	return (0);		
// }




void		death(t_values *val)
{
	// uint64_t death;
	int time;
	int death;
	int t_die;
	int tmp;

	t_die = val->utils.t_die / 1000;
	time = val->time - val->start;
	// printf("time %d\n", time);
	death = t_die - time;
	tmp = (val->last_meal - val->start) + t_die;
	// printf("death %d\n", death);
	if (tmp > time)
	{
		pthread_mutex_lock(*(&val->utils.print));
		printf("[%04llu] %i 🏴‍☠️ died\n",val->time - val->start, val->index + 1);
	// 	pthread_mutex_destroy(val->knife);
	// 	pthread_mutex_destroy(val->utils.print);
	// 	pthread_detach(*val->philos);
	}
}

int	main(void)
{
	t_values val;
	
	bzero(&val, sizeof(t_values));
	// printf("argc = %i\n", argc);
	// val.utils.t_arg = argc - 1;
	// parse(argv, &val);
	
	val.utils.n_philos = 3;

	philo_threads(&val);
	join_threads(&val);
	pthread_mutex_destroy(val.knife);
	pthread_detach(*val.philos);
	return (0);
}