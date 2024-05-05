/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:48:36 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/05 20:09:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int	time_shift(t_philo *philo)
{
	int	result;

	if (philo->program->nbr_philos % 2 != 0)
	{
		if (philo->program->tt_eat >= philo->program->tt_sleep)
		{
			result = philo->program->tt_eat - philo->program->tt_sleep;
			my_usleep(result, philo);
			usleep(50);
		}
		else if (philo->program->tt_sleep > philo->program->tt_eat)
		{
			result = philo->program->tt_sleep - philo->program->tt_eat;
			my_usleep(result, philo);
			usleep(50);
		}
	}
	return (0);
}

int	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_l);
	my_print(philo, "has taken a fork\n");
	pthread_mutex_unlock(philo->fork_l);
	my_usleep(philo->program->tt_eat + philo->program->tt_die * 1000, philo);
	return (0);
}

int	my_usleep(long long time, t_philo *philo)
{
	long long	start;

	start = gettime();
	while (!is_dead(philo))
	{
		if (gettime() - start > time)
			break ;
		usleep(50);
		/* if (time_dead(philo))
			break ; */
	}
	return (0);
}

void	my_print(t_philo *phil, char *str)
{
	if (!is_dead(phil))
	{
		pthread_mutex_lock(&phil->program->write_lock);
		printf("%lld %d %s", gettime() - phil->program->start_time, \
		phil->id, str);
		pthread_mutex_unlock(&phil->program->write_lock);
	}
}

void	*routine(void *philo)
{
	t_philo	*phil;

	phil = (t_philo *)philo;
	if (phil->program->nbr_philos == 1)
	{
		single_philo(phil);
		return (NULL);
	}
	if (phil->id % 2 == 0)
		usleep(150);
	while (!is_dead(phil) && !finished_eating(phil->program))
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
		ft_think(phil);
	}
	return (NULL);
}
