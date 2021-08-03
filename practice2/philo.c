/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:07:28 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/03 20:40:17 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dirty_eat(t_values *val)
{
	if (!val->odd_or_even)
	{
		pthread_mutex_lock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		singer(val, "⚔️  locked knife");
		pthread_mutex_lock(val->knife[val->index]);
		singer(val, "⚔️  locked knife");
		singer(val, "🥩 is eating");
		chronos(val, 0);
		usleep(val->utils.t_eat);
		pthread_mutex_unlock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		pthread_mutex_unlock(val->knife[val->index]);
	}
	else
	{
		pthread_mutex_lock(val->knife[val->index]);
		singer(val, "⚔️  locked knife");
		pthread_mutex_lock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
		singer(val, "⚔️  locked knife");
		singer(val, "🥩 is eating");
		chronos(val, 0);
		usleep(val->utils.t_eat);
		pthread_mutex_unlock(val->knife[val->index]);
		pthread_mutex_unlock(val->knife[(((val->index) + 1) % val->utils.n_philos)]);
	}
	singer(val, "🙈 is sleeping");
	usleep(val->utils.t_sleep);
	singer(val, "🤯 is thinking");
}

void	*loop(void *s_truct)
{
	t_values *val;
	val = (t_values *)s_truct;
	int	eat_count;

	val->time = 0;
	val->last_meal = 0;
	eat_count = 0;
	chronos(val, 1);
	val->start = val->time;
	while (1)
	{
		if(val->utils.m_eat > 0)
		{
			eat_count++;
			if (eat_count > val->utils.m_eat)
				break;
		}
		dirty_eat(val);
	}
	return (NULL);
}

// void		*death(void *s_truct)
// {
// 	t_values *val;
// 	val = (t_values *)s_truct;
// 	int i;
	
// 	i = 0;
// 	printf("hey %i\n", val->index);
// 	while (1)
// 	{
// 		chronos(val, 1);
// 		if ((val[i].last_meal - val[i].start) + (val->utils.t_die / 1000) < (val[i].time - val[i].start))
// 		{
// 			pthread_mutex_lock(*(&val->utils.print));
// 			// chronos(val, 1);
// 			// printf("time %llu t_die %llu\n", (val->time - val->start) + (val->utils.t_die / 1000), (val->time - val->start));
// 			printf("[%04llu] %i 🏴‍☠️ died\n",(val[i].time - val[i].start), val[i].index);
// 			// pthread_mutex_destroy(*val->knife);
// 			// pthread_detach(*val->philos);
// 			exit(1);
// 			pthread_mutex_unlock(*(&val->utils.print));
			
// 		}
// 		i++;
// 		if (i > val->utils.n_philos)
// 			i = 0;
// 	}
// 	return (NULL);
// }

void	death(t_values *val)
{
	// pthread_mutex_lock(*(&val->utils.print));
	// printf("last_meal %llu t_die %llu, time %llu index %i\n", (val->last_meal) - (val->start), (val->utils.t_die / 1000), (val->time - val->start), val->index);
	// pthread_mutex_unlock(*(&val->utils.print));
	chronos(val, 1);
	if (((val->last_meal - val->start) + (val->utils.t_die / 1000) < (val->time - val->start)) || val->utils.n_philos < 2)
	{
		if (val->utils.n_philos < 2)
		{
			usleep(val->utils.t_die);
			chronos(val, 1);
		}
			
		pthread_mutex_lock(*(&val->utils.print));
		// chronos(val, 1);
		// printf("time %llu t_die %llu\n", (val->time - val->start) + (val->utils.t_die / 1000), (val->time - val->start));
		printf("[%04llu] %i 🏴‍☠️ died\n",(val->time - val->start), val->index);
		
		exit(1);
		pthread_mutex_unlock(*(&val->utils.print));

		// val->death_flag = 1;
		// pthread_mutex_destroy(*val->knife);
		// pthread_detach(*val->philos);
	}
}

int	main(int argc, char **argv)
{
	t_values **val;
	int i;
	int x;

	i = argc;
	x = 0;
	
	 if ((argc - 1) < 4)
	 {
		 ft_put_error("Missing arguments");
		 return (1);
	 }
		
	if ((argc - 1) > 5)
	{
		ft_put_error("Too many arguments");
		return (1);
	}
		
	// bzero(val, sizeof(t_values));
	// printf("argc = %i\n", argc);
	// val[x]->utils.t_arg = argc - 1;
	// parse(argv, &val);
	
	// parse(argv, val);
	val = malloc(sizeof(t_values*) * ft_atoi(argv[1]));

	while ( x < ft_atoi(argv[1]))
	{
		val[x] = malloc(sizeof(t_values));
		bzero(val[x], sizeof(t_values));
		val[x]->utils.t_arg = argc - 1;
		val[x]->utils.n_philos = ft_atoi(argv[1]);
		val[x]->utils.t_die = (ft_atoi(argv[2]) * 1000);
		val[x]->utils.t_eat = (ft_atoi(argv[3]) * 1000);
		val[x]->utils.t_sleep = (ft_atoi(argv[4]) * 1000);
		if (val[x]->utils.t_arg > 4)
			val[x]->utils.m_eat = ft_atoi(argv[5]);
		x++;
	}
	// parse(argv, *val);
	// val->utils.n_philos = ft_atoi(argv[1]);
	// val.utils.n_philos = argv;

	philo_threads(val);
	join_threads(val);
	system ("leaks philo");
	// death_thread(*val);
	// pthread_mutex_destroy(val.knife);
	// pthread_detach(*val.philos);
	return (0);
}