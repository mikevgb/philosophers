/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   besta_philo_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:49:45 by mvillaes          #+#    #+#             */
/*   Updated: 2021/05/13 21:10:25 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int philo_n;
    int t_2_die;
    int t_2_eat;
    int t_2_sleep;
    int eat_loops;

    philo_n = argv[1];
    t_2_die = argv[2];
    t_2_eat = argv[3];
    t_2_sleep = argv[4];

    if(argv[5] != NULL)
        eat_loops = argv[5];

    philo(philo_n, t_2_eat);
}

void    eat(int t_2_eat)
{
    usleep(t_2_eat);
}

void    philo(int philo_n, int t_2eat)
{
    int i;
    int thread;
    int eat;

    eat = usleep(t_2_eat);

    pthread_t philo[philo_n];
    i = 0;
    while(i < philo_n)
    {
        thread = pthread_create(&pid[i], NULL, &eat, NULL);
        if (thread != 0)
            printf("Error in thread creation\n");
        i++;
    }


}