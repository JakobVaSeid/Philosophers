/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:13:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/01 14:36:16 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int init_mutex(t_program *program)
{
    int i;

    i = 0;
    while(i < program->nbr_philos)
    {
        pthread_mutex_init(&program->forks[i], NULL);
        i++;
    }
    if(pthread_mutex_init(&program->write_lock, NULL))
        return (1);
    return (0);
}

//create the philosphers
int init_philo(t_program *program)
{
    int i;
    
    i = 0;
    program->philo = malloc(sizeof(t_philo) * program->nbr_philos);
    if (!program->philo)
        return (1);
    program->forks = malloc(sizeof(pthread_mutex_t) * program->nbr_philos);
    if (!program->forks)
        return (1);
    while(i < program->nbr_philos)
    {
        program->philo[i].id = i + 1;
        program->philo[i].id_thread = i;
        program->philo[i].fork_r = &program->forks[i];
        program->philo[i].fork_l = &program->forks[(i + 1) % program->nbr_philos];
        program->philo[i].write_lock = &program->write_lock;
        program->philo[i].program = program;
        program->philo[i].is_dead = false;
        program->one_is_dead = &program->philo[i].is_dead;
        i++;
    }
    return (0);
}

//initialize the program
int init_prgm(t_program *program, int argc, char **argv)
{
    if (!program)
        return (1);
    program->nbr_philos = ft_atoi(argv[1]);
    program->tt_die = ft_atoi(argv[2]);
    program->tt_eat = ft_atoi(argv[3]);
    program->tt_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        program->meals = ft_atoi(argv[5]);
    else
        program->meals = -1;
    program->finished_eating = 0;
    //printf("Number of philos: %d\n", program->nbr_philos);
    //printf("Time to die: %d\n", program->tt_die);
    //printf("Time to eat: %d\n", program->tt_eat);
    //printf("Time to sleep: %d\n", program->tt_sleep);
    //printf("Meals: %d\n", program->meals);
    return (0);
}

int init(t_program *program, int argc, char **argv)
{
    if (!program)
        return (1);
    if(init_prgm(program, argc, argv))
        return(1);
    if(init_philo(program))
        return(1);
    if(init_mutex(program))
        return(1);
    return (0);
}
