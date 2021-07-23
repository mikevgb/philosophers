/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/23 21:06:18 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_values *values, int odd_or_even)
{
	singer(values, "🥩 is eating");
	ft_sleep(2000);
	if (!odd_or_even)
	{
		if (values->index == 0)
			pthread_mutex_unlock(*(&values->knife + values->utils.n_philos));
		else 
			pthread_mutex_unlock(*(&values->knife) - 1);
		pthread_mutex_unlock(*(&values->knife));
	}	
	else
	{
		pthread_mutex_unlock(*(&values->knife));
		pthread_mutex_unlock(*(&values->knife) - 1);
	}
	singer(values, "⚔️  let knifes");
}

int		lock_knifes(t_values *values, int flag)
{
	if (!flag)
	{

		pthread_mutex_lock(*(&values->knife));
		singer(values, "🗡  locked right knife");
		return (1);
	}
	else
	{
		if (values->index == 0)
		{
			pthread_mutex_lock(*(&values->knife + values->utils.n_philos));
			singer(values, "🔪 locked left knife");
		}
		else
		{
			pthread_mutex_lock(*(&values->knife) - 1);
			singer(values, "🔪 locked left knife");
		}
		// pthread_mutex_lock(*(&values->knife + 1 % 6));
		// singer(values, "🔪 locked left knife");
		return (1);
	}
}

void	eat(t_values *values)
{
	int odd_or_even;

	odd_or_even = values->index % 2;
	if (!odd_or_even)
	{
		if (lock_knifes(values, 0) && lock_knifes(values, 1))
			eating(values, odd_or_even);
	}
	else
	{
		if (lock_knifes(values, 1) && lock_knifes(values, 0))
			eating(values, odd_or_even);
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
		eat(val);
		philo_sleep(val);
		singer(val, "🤯 started thinking");
	}
	return (NULL);
}

int	main(void)
{
	t_values values;
	
	// bzero(&values, sizeof(t_values)); //this may go on struct array creation
	values.utils.n_philos = 6;
	values.utils.t_eat = 2000;
	values.utils.t_sleep = 1000;
	values.utils.t_die = 400;

	make_threads(&values);
	join_threads(&values);
	pthread_mutex_destroy(values.knife);
	pthread_detach(*values.philos);
	return (0);
}