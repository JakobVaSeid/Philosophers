/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:48:36 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/01 14:50:46 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int ft_sleep(t_philo *philo)
{
    printf("%lld %d is sleeping\n", gettime() - philo->program->start_time, philo->id);
    return (0);
}

int ft_think(t_philo *philo)
{
    printf("%lld %d is thinking\n",gettime() - philo->program->start_time, philo->id);
    return (0);
}

int ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->fork_r);
    printf("%lld %d has taken a fork\n", gettime() - philo->program->start_time, philo->id);
    pthread_mutex_lock(philo->fork_l);
    printf("%lld %d has taken a fork\n", gettime() - philo->program->start_time, philo->id);
    pthread_mutex_unlock(philo->fork_r);
    pthread_mutex_unlock(philo->fork_l);
    philo->last_meal = gettime();
    printf("%lld %d is eating\n", gettime() - philo->program->start_time, philo->id);
    //printf("________________________________\n");
    philo->meals_eaten++;
    //printf("Meals_eaten: %d\n", philo->meals_eaten);
    return (0);
}

void *routine(void *philo)
{
    t_philo *phil = (t_philo *)philo;
    
    while(phil->meals_eaten <= phil->program->meals)
    {
            ft_eat(phil);
            my_usleep(phil->program->tt_eat);
            ft_sleep(phil);
            my_usleep(phil->program->tt_sleep);
            ft_think(phil);
    }
    phil->program->finished_eating = 1;
    return (NULL);
}