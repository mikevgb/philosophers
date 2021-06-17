/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:36:34 by mvillaes          #+#    #+#             */
/*   Updated: 2021/06/17 22:16:47 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_WAIT 10;

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int	n_philos;
	int	t_2_die;
	int	t_2_eat;
	int	t_2_sleep;
	int	eat_num;
	int	total_arg;
}	t_data;

/* main */

int		main(int argc, char **argv);

/* parse */

void	parse(char **argv, t_data *data);

/* utils */

void	ft_putstr(char *str);
void	*ft_bzero(void *ft, size_t i);
int		ft_isdigit(int c);
int		ft_atoi(char const *str);

#endif