/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 18:08:50 by mvillaes          #+#    #+#             */
/*   Updated: 2021/07/31 22:38:35 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pthread.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"
#include "string.h" //REMOVE, FOR BZERO



typedef struct s_utils{
	pthread_mutex_t *print;
	pthread_mutex_t	*death;
	int				t_arg;
	int				n_philos;
	uint64_t		t_eat;
	uint64_t		t_sleep;
	int				m_eat;
	uint64_t			t_die;
}	t_utils;

typedef struct s_values{
	int				odd_or_even;
	uint64_t		last_meal;
	// uint64_t		death;
	int				c_eat;
	int				t_arg;
	int				index;
	uint64_t		time;
	
	pthread_t 		*philos;
	pthread_mutex_t **knife;
	t_utils			utils;
	uint64_t		start;
	struct timeval	end;
}	t_values;


int		main(int argc, char **argv);
void	*loop(void *s_truct);
// void	*death(void *s_truct);
void	death(t_values *val);

/* threads_mutex.c */

void	fork_mutex(t_values *values);
void	philo_threads(t_values **val);
void	join_threads(t_values **values);
void	singer_mutex(t_values *values);
// void	death_thread(t_values *values);
void	death_mutex(t_values *values);

/* utils.c */

// void	ft_putnbr_fd(int n, int fd);
// void	ft_putchar_fd(char c, int fd);
// void	ft_sleep(useconds_t i);
void	singer(t_values *values, char *str);
void	philo_sleep(t_values *values);
void	chronos(t_values *values, int flag);
void	parse(char **argv, t_values *val);

/* utils folder */

int	ft_atoi(char const *str);
void	*ft_bzero(void *ft, size_t i);
int	ft_isdigit(int c);
void	ft_putstr(char *str);
void	ft_put_error(char *str);
