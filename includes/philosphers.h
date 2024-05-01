/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:55:26 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/01 14:15:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>


//allowed functions
//memset, printf, malloc, free, write,
//usleep, gettimeofday, 
//pthread_create,
//pthread_detach, pthread_join, pthread_mutex_init,
//pthread_mutex_destroy, pthread_mutex_lock,
//pthread_mutex_unlock

typedef struct s_philo t_philo;

typedef struct s_program
{
    int             nbr_philos;
    int             tt_die;
    int             tt_eat;
    int             tt_sleep;
    int             finished_eating;
    //int           one_died;
    //t_philo       philos[50];
    //int           fork[50];
    bool            *one_is_dead;
    int             meals;
    long long       start_time;
    pthread_mutex_t *forks;
    t_philo         *philo;
    pthread_mutex_t write_lock;
} t_program;

typedef struct s_philo
{
    pthread_t       id_thread;
    int             id;
    int             last_meal;
    int             meals_eaten;
    bool            is_dead;
    pthread_mutex_t *fork_l;
    pthread_mutex_t *fork_r;
    pthread_mutex_t *write_lock;
    t_program       *program;
} t_philo;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////source///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//init.c
int init_mutex(t_program *program);
int init_philo(t_program *program);
int init_prgm(t_program *program, int argc, char **argv);
int init(t_program *program, int argc, char **argv);

//utils.c
int	ft_atoi(const char *str);
long long gettime();
int my_usleep(long long time);
void *check_if_dead(void *philo);

//routine.c
int ft_sleep(t_philo *philo);
int ft_think(t_philo *philo);
int ft_eat(t_philo *philo);
void *routine(void *philo);

