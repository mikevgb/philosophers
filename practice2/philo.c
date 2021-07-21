/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/21 21:50:39 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
}

void	*think(t_values *values)
{
	printf("Philo %i 🤯 started thinking\n", values->index);
	return (NULL);
}

void	singer(t_values *values, char *str)
{
	values->print = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(values->print, NULL);
	pthread_mutex_lock(values->print);
	printf("Philo %i %s\n", values->index, str);
	pthread_mutex_unlock(values->print);
}

void	eating(t_values *values, int odd_or_even)
{
	if (odd_or_even == 0)
	{
		singer(values, "🥩 is eating");
		ft_sleep(2000);
		pthread_mutex_unlock(*(&values->knife));
		pthread_mutex_unlock(*(&values->knife) + 1);
		singer(values, "⚔️  let knifes");
	}
	else
	{
		singer(values, "🥩 is eating");
		ft_sleep(2000);
		pthread_mutex_unlock(*(&values->knife));
		pthread_mutex_unlock(*(&values->knife) - 1);
		singer(values, "⚔️  let knifes");
	}
}

void	eat(t_values *values)
{
	int odd_or_even;
	int is_eating;
	
	odd_or_even = values->index % 2;
	is_eating = 0;
	if (odd_or_even == 0)
	{
		pthread_mutex_lock(*(&values->knife));
		singer(values, "🗡  right knife locked");
		is_eating += 1;
		pthread_mutex_lock(*(&values->knife) - 1);
		singer(values, "🔪 left knife locked");
		is_eating += 1;
		if (is_eating == 2)
		{
			eating(values, odd_or_even);
			is_eating = 0;
		}
	}
	else
	{
		pthread_mutex_lock(*(&values->knife) - 1);
		singer(values, "🔪 left knife locked");
		is_eating += 1;
		pthread_mutex_lock(*(&values->knife));
		singer(values, "🗡  right knife locked");
		is_eating += 1;
		if (is_eating == 2)
		{
			eating(values, odd_or_even);
			is_eating = 0;
		}	
	}
}

void	philo_sleep(t_values *values)
{
	printf("Philo %i 🙈 is sleeping\n", values->index);
	ft_sleep(2000);
}

void	*loop(void *s_truct)
{
	t_values *val;

	val = (t_values *)s_truct;

	while (1)
	{
		eat(val);
		philo_sleep(val);
		think(val);
	}
	return (NULL);
}

int	main(void)
{
	t_values values;
	
	bzero(&values, sizeof(t_values));
	values.n_philos = 5;
	values.t_eat = 2000;
	values.t_sleep = 1000;
	values.t_die = 4000;
	make_threads(&values);
	join_threads(&values);
	pthread_mutex_destroy(values.knife);
	pthread_detach(*values.philos);
	return (0);
}