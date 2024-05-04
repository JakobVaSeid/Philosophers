/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:48:36 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/04 16:15:14 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int	ft_sleep(t_philo *philo)
{
	my_print(philo, "is sleeping\n");
	return (0);
}

int	ft_think(t_philo *philo)
{
	int	result;

	my_print(philo, "is thinking\n");
	if (philo->program->nbr_philos % 2 != 0)
	{
		if (philo->program->tt_eat >= philo->program->tt_sleep)
		{
			result = philo->program->tt_eat - philo->program->tt_sleep;
			my_usleep(result, philo->program);
			usleep(100);
		}
	}
	return (0);
}

int	ft_eat_even(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_r);
	my_print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_l);
	my_print(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->program->eaten_lock);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->program->eaten_lock);
	my_print(philo, "is eating\n");
	my_usleep(philo->program->tt_eat, philo->program);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(&philo->program->eaten_lock);
	if (philo->program->meals >= 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->eaten_lock);
	return (0);
}

int	ft_eat_uneven(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	my_print(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->fork_r);
	my_print(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->program->eaten_lock);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->program->eaten_lock);
	my_print(philo, "is eating\n");
	my_usleep(philo->program->tt_eat, philo->program);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_lock(&philo->program->eaten_lock);
	if (philo->program->meals >= 0)
		philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->eaten_lock);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
		ft_eat_even(philo);
	else
		ft_eat_uneven(philo);
	return (0);
}

void	*routine(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	if (phil->id % 2 == 0)
		usleep(150);
	while (!is_dead(phil->program) && !finished_eating(phil->program))
	{
		ft_eat(phil);
		if (phil->program->meals && all_eaten(phil->program))
		{
			pthread_mutex_lock(&phil->program->eaten_lock);
			phil->program->finished_eating = 1;
			pthread_mutex_unlock(&phil->program->eaten_lock);
			break ;
		}
		ft_sleep(phil);
		my_usleep(phil->program->tt_sleep, phil->program);
		ft_think(phil);
	}
	return (NULL);
}
