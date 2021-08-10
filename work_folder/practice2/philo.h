/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:08:50 by mvillaes          #+#    #+#             */
/*   Updated: 2021/08/10 17:48:27 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "pthread.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "sys/time.h"

typedef struct s_utils
{
	pthread_mutex_t	*print;
	int				quit_death;
	int				t_arg;
	int				n_philos;
	int				m_eat;
	int				eat_c;
	int				*feed;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	uint64_t		t_die;
}	t_utils;

typedef struct s_values
{
	pthread_mutex_t	**knife;
	pthread_t		*philos;
	int				*death_flag;
	int				odd_or_even;
	int				index;
	t_utils			utils;
	uint64_t		last_meal;
	uint64_t		time;
	uint64_t		start;
	struct timeval	end;
}	t_values;

int		main(int argc, char **argv);
void	*loop(void *s_truct);

/* threads_mutex.c */

void	philo_threads(t_values **val);
void	join_threads(t_values **values);
void	singer_mutex(t_values *values);
int		special_philo(t_values *val);
void	freedom(t_values **val);

/* utils.c */

void	singer(t_values *values, char *str);
void	chronos(t_values *values, int flag);
int		check(int argc, char **argv);
void	hang_over(t_values *val, int wait);
void	death(t_values *val);

/* utils folder */

int		ft_atoi(char const *str);
void	*ft_bzero(void *ft, size_t i);
int		ft_isdigit(int c);
void	ft_putstr(char *str);
void	ft_put_error(char *str);

#endif