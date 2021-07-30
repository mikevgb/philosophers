/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/30 17:32:58 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dirty_eat(t_values *val)
{
	if (!val->odd_or_even)
	{
		pthread_mutex_lock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		singer(val, "⚔️  locked right knife");
		pthread_mutex_lock(val->knife[val->index]);
		singer(val, "⚔️  locked left knife");
		singer(val, "🥩 is eating");
		usleep(val->utils.t_eat);
		pthread_mutex_unlock(val->knife[val->index]);
		pthread_mutex_unlock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
	}
	else
	{
		pthread_mutex_lock(val->knife[val->index]);
		singer(val, "⚔️  locked left knife");
		pthread_mutex_lock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		singer(val, "⚔️  locked right knife");
		singer(val, "🥩 is eating");
		usleep(val->utils.t_eat);
		pthread_mutex_unlock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		pthread_mutex_unlock(val->knife[val->index]);
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




void		*death(void *s_truct)
{
	t_values *val;
	val = (t_values *)s_truct;
	// uint64_t death;
	int time;
	int death;
	int t_die;
	int tmp;

	
	while(1)
	{
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
	
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_values **val;
	int i;
	int x;

	i = argc;
	x = 0;
	
	// bzero(val, sizeof(t_values));
	// printf("argc = %i\n", argc);
	// val.utils.t_arg = argc - 1;
	// parse(argv, &val);
	
	// parse(argv, val);
	val = malloc(sizeof(t_values*) * ft_atoi(argv[1]));

	while ( x < ft_atoi(argv[1]))
	{
		val[x] = malloc(sizeof(t_values));
		val[x]->utils.n_philos = ft_atoi(argv[1]);
		x++;
	}
	// val->utils.n_philos = ft_atoi(argv[1]);
	// val.utils.n_philos = argv;

	philo_threads(val);
	join_threads(val);
	// pthread_mutex_destroy(val.knife);
	// pthread_detach(*val.philos);
	return (0);
}