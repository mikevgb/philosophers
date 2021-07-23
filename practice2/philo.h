/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:08:50 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/23 20:35:51 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "string.h" //REMOVE, FOR BZERO

// #define L_KNIFE 1 % 5

typedef struct s_utils{
	pthread_mutex_t *print;
	int				n_philos;
	int				t_eat;
	int				t_sleep;
	int				t_die;
}	t_utils;

typedef struct s_values{
	int				index;
	uint64_t		time;
	pthread_t 		*philos;
	pthread_mutex_t *knife;
	t_utils			utils;
	uint64_t		start;
	struct timeval	end;
}	t_values;

int		main(void);
void	*loop(void *s_truct);

/* threads_mutex.c */

void	make_mutex(t_values *values);
void	make_threads(t_values *values);
void	join_threads(t_values *values);
void	singer_mutex(t_values *values);

/* utils.c */

void	ft_sleep(long i);
void	singer(t_values *values, char *str);
void	philo_sleep(t_values *values);
void	chronos(t_values *values);

