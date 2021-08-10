/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 19:47:18 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/18 20:04:15 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_philos(t_data *data)
{
	int	*philo;

	philo = (int)malloc(data->n_philos * sizeof(int));
	if (philo == NULL)
		ft_put_error("philo malloc failed");
	return (philo);
}
