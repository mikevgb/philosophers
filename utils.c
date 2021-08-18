/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:11:38 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/18 18:13:25 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	singer(t_values *val, char *str)
{
	chronos(val, 1);
	pthread_mutex_lock(*(&val->utils.print));
	if (!*val->death_flag)
		printf("[%04llu] %i %s\n", val->time - val->start, val->index + 1, str);
	pthread_mutex_unlock(*(&val->utils.print));
}

void	chronos(t_values *val, int flag)
{
	gettimeofday(&val->end, NULL);
	if (!flag)
		val->last_meal = ((((val->end.tv_sec) * \
		(uint64_t)1000 + (val->end.tv_usec) / 1000)));
	else
		val->time = ((((val->end.tv_sec) * (uint64_t)1000 + \
		(val->end.tv_usec) / 1000)));
}

void	hang_over(t_values *val, int wait)
{
	uint64_t	end;

	chronos(val, 1);
	end = val->time - val->start + (wait / 1000);
	while (val->time - val->start < end)
	{
		usleep(val->utils.n_philos);
		chronos(val, 1);
	}
}

int	check(int argc, char **argv)
{
	int	x;

	x = 0;
	if ((argc - 1) < 4 || (argc - 1) > 5)
	{
		ft_put_error("Bad arguments");
		return (1);
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 \
	|| ft_atoi(argv[4]) < 1)
	{
		ft_put_error("Bad arguments");
		return (1);
	}
	if (argc > 5)
	{
		if (ft_atoi(argv[5]) < 1)
		{
			ft_put_error("Bad must_eat value");
			return (1);
		}
	}
	return (0);
}

void	death(t_values *val)
{
	int	i;

	i = 0;
	usleep(100);
	while (i < val[i].utils.n_philos)
	{
		chronos(val, 1);
		if (((val[i].last_meal - val[i].start) + (val[i].utils.t_die / 1000) \
		< (val[i].time - val[i].start)) || val[i].utils.n_philos < 2 || \
		val->utils.t_eat > val->utils.t_die)
		{
			if (val[i].utils.n_philos < 2 || \
			val->utils.t_eat > val->utils.t_die)
				hang_over(val, val[i].utils.t_die);
			printf("[%04llu] %i 🏴‍☠️ died\n", (val[i].time - val[i].start), \
			val[i].index + 1);
			*val[i].death_flag = 1;
			break ;
		}
		if (*val->utils.feed == 1)
			break ;
	}
}
