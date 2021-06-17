/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:36:19 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/17 22:27:16 by mvillaes         ###   ########.fr       */
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
	if (data.total_arg != 4 || data.total_arg > 5)
	{
		ft_putstr("Error: Incorrect number of arguments\n");
		exit (1);
	}
	parse(argv, &data);
	print_input(&data);
	return (0);
}
