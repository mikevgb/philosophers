/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/24 21:59:05 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_values *val, int odd_or_even)
{
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
	int i;
	val = (t_values *)s_truct;
	
	val->time = 0;
	i = 0;
	chronos(val);
	val->start = val->time;
	while (i < val->utils.m_eat)
	{
		dirty_eat(val);
		philo_sleep(val);
		singer(val, "🤯 is thinking");
		i++;
	}
	return (NULL);
}

int	main(void)
{
	t_values val;
	
	// printf("argc = %i\n", argc);
	// val.utils.t_arg = argc - 1;
	// parse(argv, &val);
	
	val.utils.n_philos = 5;
	make_threads(&val);
	join_threads(&val);
	pthread_mutex_destroy(val.knife);
	pthread_detach(*val.philos);
	return (0);
}