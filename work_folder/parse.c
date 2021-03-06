/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:58:24 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/24 20:18:59 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parse(char **argv, t_data *data)
{
	if (data->total_arg < 4)
		ft_put_error("Missing arguments");
	if (data->total_arg > 5)
		ft_put_error("Too many arguments");
	data->n_philos = ft_atoi(argv[1]);
	data->t_2_die = ft_atoi(argv[2]);
	data->t_2_eat = ft_atoi(argv[3]);
	data->t_2_sleep = ft_atoi(argv[4]);
	if (data->total_arg > 4)
		data->eat_num = ft_atoi(argv[5]);
	// data->forks = data->n_philos;
	// data->left = (i + data->n_philos - 1) % 5;
	// data->right = (i + 1) % 5;
}
