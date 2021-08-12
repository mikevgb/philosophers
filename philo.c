/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/11 17:44:21 by mvillaes         ###   ########.fr       */
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
	val->utils.eat_c++;
	chronos(val, 0);
	hang_over(val, val->utils.t_eat);
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
	val->utils.eat_c++;
	chronos(val, 0);
	hang_over(val, val->utils.t_eat);
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
	hang_over(val, val->utils.t_sleep);
	singer(val, "🤯 is thinking");
}

void	*loop(void *s_truct)
{
	t_values	*val;
	static int	death_flag;
	int			eat_count;
	static int	feed;

	val = (t_values *)s_truct;
	death_flag = 0;
	feed = 0;
	val->death_flag = &death_flag;
	val->utils.feed = &feed;
	val->time = 0;
	val->last_meal = 0;
	eat_count = 0;
	chronos(val, 1);
	val->start = val->time;
	while (!*val->death_flag)
	{
		if (!special_philo(val))
			break ;
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
	death(*val);
	join_threads(val);
	freedom(val);
	return (0);
}
