/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirty_philo_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillaes <mvillaes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:13:43 by mvillaes          #+#    #+#             */
/*   Updated: 2021/05/11 23:24:19 by mvillaes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int     main(int argc, char **argv)
{
    int philo_num;
    int t_2_die;
    int t_2_eat;
    int t_2_sleep;
    int eat_loops; //optional
    int i;
    int arg_num;

    arg_num = argc;
    eat_loops = 0;
    i = 0;

    while (i < arg_num && arg_num > 1)
    {
        philo_num = argv[i];
        if(philo_num < 2)
            printf("Error: We need more than one philo\n");
        t_2_die = argv[i];
        t_2_eat = argv[i];
        t_2_sleep = argv[i];
        if(arg_num == 4)
            eat_loops = argv[i];
        if(arg_num > 4)
            printf("Error: Too many arguments\n");
    }

    printf("\nphilo_num %i\n", philo_num);
    printf("\nt_2_die %i\n", t_2_die);
    printf("\nt_2_eat %i\n", t_2_eat);
    printf("\nt_2_sleep %i\n", t_2_sleep);
    printf("\neat_loops %i\n", eat_loops);

    int forks;

    forks = philo_num;

    //create thread
    int thread; //thread behaves like a control tool
                //pthread_create is a kind of malloc
                //that we use to "alloc" threads
    int x; //counter, that limits in while how many 
            //threads we will create;
    pthread_t ptid[3]; //kind of list of threads, should be in .h?
    
    x = 0;
    while(x < 3)
    {
        //create threads in loop, will call philo function
        thread = pthread_create(&pid[x], NULL, &function, NULL);
        if(thread != 0) //Kind of checker of thread creation
            printf("Cant create thread\n");
        x++;
    }

    //join is used for wait to the thread to finish the job
    //i guess it releases and puts it in a pool so it can be
    //reused? idk
    pthread_join(ptid[1], NULL);
    pthread_join(ptid[2], NULL);
    pthread_join(ptid[3], NULL);

    //detach is like killing the thread, probably will have to
    //be used when the philo dies.
    pthread_detach(ptid[x]);

    //MUTEX https://www.thegeekstuff.com/2012/05/c-mutex-examples/
    //mutex are used for thread synchronization
    //is a lock that we set before using a shared resource
    //and release after using it, kind of reservation.
    //when lock is set, no other thread can access the
    //locked region of code.(eat, sleep, think ft's???)
    //--update i guess it will be the fork!
    // it should be used inside inside the function that
    // we want to lock, at the start and unlocked at the end
    //
    //initialize the "list" of mutex (guess this will be in .h)
    pthread_mutex_t lock;
    //fist we initialize with init
    pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
    //lock the code region
    pthread_mutex_lock(pthread_mutex_t *mutex);
    //unlock
    pthread_mutex_unlock(pthread_mutex_t *mutex);
    //destroy
    pthread_mutex_destroy(pthread_mutex_t *mutex);

    //example
    //initialize the thread
    pthread_t pid[2];
    //initialize the lock
    pthread_mutex_t lock;

    void *ft_do_something(void *arg)
    {
        //lock thread
        pthread_mutex_lock(&lock);

        //start the job...
        //...finish the job

        //unlock thread
        pthread_mutex_unlock(&lock);

    }

    int main(void)
    {
        // initialize mutex and check if
        // has been succesfully initialaized
        if (pthread_mutex_init(&lock, NULL) != 0)
            printf("mutex init failed\n");
        //initialize the thread and ft that has mutex
        pthread_create(&(pid[i], NULL, &ft_do_something, NULL));

        //start the other threads;
        pthread_join(pid[0], NULL);
        pthread_join(pid[1], NULL);
        //destroy, not sure why, because is unlocked when
        //ft_do_something ends
        pthread_mutex_destroy(&lock);
        return(0);
        
    }

    //PROBLEMS

    //RACE CONDITION:
    //if 2 philos try to get the same fork they will compite
    //for it, and one will not be able to eat

    //DEADLOCK;
    //if all philos take one fork then all be waiting
    //forever because one should release the missing fork
    //which wont happend and they will die
    

    //loop * philo
    int eat;
    int sleep;
    int think;
    int end;
    int forks_availabe;

    eat = 0;
    sleep = 0;
    think = 0;
    forks_availabe = forks;

    while(eat = 1 && forks_availabe > 1)
    {
        forks_availabe -= 2;
        think = 0;
        sleep = 0;
        if (eat == end)
        {
            sleep = 1;
            forks_available += 2;
        }
            
    }
    
    while(sleep = 1)
    {
        think = 0;
        eat = 0;
        if (sleep == end)
            think = 1;
    }

    while(think = 1)
    {
        eat = 0;
        sleep = 0;
        if (think == end)
            eat = 1;
    }
}

//philos have 3 states
//so if we have a minimum of 3 philos
//each one will start in one of the states
//every extra philo will be spread across
//the 3 states (how many can we recive?)


