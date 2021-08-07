/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/07 20:10:51 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	even_eat(t_values *val)
{
	pthread_mutex_lock(val->knife[(((val->index) + 1) \
	% val->utils.n_philos)]);
	singer(val, "⚔️  locked knife");
	pthread_mutex_lock(val->knife[val->index]);
	singer(val, "⚔️  locked knife");
	singer(val, "🥩 is eating");
	chronos(val, 0);
	usleep(val->utils.t_eat);
	pthread_mutex_unlock(val->knife[(((val->index) + 1) \
	% val->utils.n_philos)]);
	pthread_mutex_unlock(val->knife[val->index]);
}

static void	odd_eat(t_values *val)
{
	pthread_mutex_lock(val->knife[val->index]);
	singer(val, "⚔️  locked knife");
	pthread_mutex_lock(val->knife[(((val->index) + 1) \
	% val->utils.n_philos)]);
	singer(val, "⚔️  locked knife");
	singer(val, "🥩 is eating");
	chronos(val, 0);
	usleep(val->utils.t_eat);
	pthread_mutex_unlock(val->knife[val->index]);
	pthread_mutex_unlock(val->knife[(((val->index) + 1) \
	% val->utils.n_philos)]);
}

static void	dirty_eat(t_values *val)
{
	if (!val->odd_or_even)
		even_eat(val);
	else
		odd_eat(val);
	singer(val, "🙈 is sleeping");
	usleep(val->utils.t_sleep);
	singer(val, "🤯 is thinking");
}

void	*loop(void *s_truct)
{
	t_values	*val;
	static int	death_flag;
	int			eat_count;

	val = (t_values *)s_truct;
	death_flag = 0;
	val->death_flag = &death_flag;
	val->time = 0;
	val->last_meal = 0;
	eat_count = 0;
	chronos(val, 1);
	val->start = val->time;
	while (!*val->death_flag)
	{
		if (val->utils.m_eat > 0)
		{
			eat_count++;
			if (eat_count > val->utils.m_eat)
				break ;
		}
		dirty_eat(val);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_values	**val;
	int			x;

	x = 0;
	check(argc, argv);
	val = malloc(sizeof(t_values *) * ft_atoi(argv[1]) + 1);
	while (x < ft_atoi(argv[1]))
	{
		val[x] = malloc(sizeof(t_values));
		ft_bzero(val[x], sizeof(t_values));
		val[x]->utils.t_arg = argc - 1;
		val[x]->utils.n_philos = ft_atoi(argv[1]);
		val[x]->utils.t_die = ft_atoi(argv[2]) * 1000;
		val[x]->utils.t_eat = ft_atoi(argv[3]) * 1000;
		val[x]->utils.t_sleep = ft_atoi(argv[4]) * 1000;
		if (val[x]->utils.t_arg > 4)
			val[x]->utils.m_eat = ft_atoi(argv[5]);
		x++;
	}
	philo_threads(val);
	join_threads(val);
	return (0);
}
