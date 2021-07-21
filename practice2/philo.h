/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:08:50 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/21 21:50:42 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "string.h" //REMOVE, FOR BZERO

typedef struct s_values{
	int			n_philos;
	int			t_eat;
	int			t_sleep;
	int			t_die;
	long		j;
	int			index;
	pthread_t 	*philos;
	pthread_mutex_t *knife;
	pthread_mutex_t *print;
}	t_values;

int		main(void);
void	*loop(void *s_truct);

void	make_mutex(t_values *values);
void	make_threads(t_values *values);
void	join_threads(t_values *values);