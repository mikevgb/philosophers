/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:36:19 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/18 19:55:09 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_input(t_data *data)
{
	printf("Number of philos = %i\n", data->n_philos);
	printf("Time 2 die = %i\n", data->t_2_die);
	printf("Time 2 eat = %i\n", data->t_2_eat);
	printf("Time 2 sleep = %i\n", data->t_2_sleep);
	printf("Eat num = %i\n", data->eat_num);
	printf("Total args = %i\n", data->total_arg);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	data.total_arg = argc - 1;
	parse(argv, &data);
	print_input(&data);

	philo(&data);
	pthread_exit(NULL);
	return (0);
}
