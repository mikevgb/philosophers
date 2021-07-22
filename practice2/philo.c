/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/22 22:03:29 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(long i)
{
	long	sleep_time;

	sleep_time = i * 1000;
	usleep(sleep_time);
}

// void	chronos(t_values *values)
// {

// }

void	singer(t_values *values, char *str)
{
	pthread_mutex_lock(values->utils.print);
	printf("[%llu] Philo %i %s\n",values->time, values->index, str);
	pthread_mutex_unlock(values->utils.print);
}

void	*think(t_values *values)
{
	singer(values, "🤯 started thinking");
	return (NULL);
}



void	eating(t_values *values, int odd_or_even)
{
	if (odd_or_even == 0)
	{
		singer(values, "🥩 is eating");
		ft_sleep(1500);
		pthread_mutex_unlock(*(&values->knife));
		// pthread_mutex_unlock(*(&values->knife) + 1 % 5);
		pthread_mutex_unlock(values[(values->index + 1) % values->utils.n_philos].knife);
		singer(values, "⚔️  let knifes");
	}
	else
	{
		singer(values, "🥩 is eating");
		ft_sleep(1500);
		// pthread_mutex_unlock(*(&values->knife) + 1 % 5);
		pthread_mutex_unlock(values[(values->index + 1) % values->utils.n_philos].knife);
		pthread_mutex_unlock(*(&values->knife));
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
		singer(values, "🗡  locked right knife");
		is_eating += 1;
		pthread_mutex_lock(values[(values->index + 1) % values->utils.n_philos].knife);
		singer(values, "🔪 locked left knife");
		is_eating += 1;
		if (is_eating == 2)
		{
			eating(values, odd_or_even);
			is_eating = 0;
		}
	}
	else
	{
		// pthread_mutex_lock(*(&values->knife) + 1 % 5);
		pthread_mutex_lock(values[(values->index + 1) % values->utils.n_philos].knife);
		singer(values, "🔪 locked left knife");
		is_eating += 1;
		pthread_mutex_lock(*(&values->knife));
		singer(values, "🗡  locked right knife");
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
	singer(values, "🙈 is sleeping");
	ft_sleep(1800);
}

void	*loop(void *s_truct)
{
	t_values *val;
	val = (t_values *)s_truct;
	
	val->time = 0;
	gettimeofday(&val->start, NULL);
	while (1)
	{
		eat(val);
		gettimeofday(&val->end, NULL);
		val->time = ((&val->end.tv_sec - &val->start.tv_sec) * 1000 + (&val->end.tv_usec - &val->start.tv_usec) / 1000);
		philo_sleep(val);
		gettimeofday(&val->end, NULL);
		val->time = ((&val->end.tv_sec - &val->start.tv_sec) * 1000 + (&val->end.tv_usec - &val->start.tv_usec) / 1000);
		think(val);
		gettimeofday(&val->end, NULL);
		val->time = ((&val->end.tv_sec - &val->start.tv_sec) * 1000 + (&val->end.tv_usec - &val->start.tv_usec) / 1000);
	}
	return (NULL);
}

int	main(void)
{
	t_values values;
	
	bzero(&values, sizeof(t_values)); //this may go on struct array creation
	values.utils.n_philos = 5;
	values.t_eat = 2000;
	values.t_sleep = 1000;
	values.t_die = 4000;

	make_threads(&values);
	join_threads(&values);
	pthread_mutex_destroy(values.knife);
	pthread_detach(*values.philos);
	return (0);
}