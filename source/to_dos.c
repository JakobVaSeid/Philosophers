/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_dos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:59:34 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/05 20:10:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int	ft_sleep(t_philo *philo)
{
	my_print(philo, "is sleeping\n");
	my_usleep(philo->program->tt_sleep, philo);
	return (0);
}

int	ft_think(t_philo *philo)
{
	my_print(philo, "is thinking\n");
	time_shift(philo);
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
	my_usleep(philo->program->tt_eat, philo);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
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
	my_print(philo, "is eating\n");
	my_usleep(philo->program->tt_eat, philo);
	pthread_mutex_lock(&philo->program->eaten_lock);
	philo->last_meal = gettime();
	pthread_mutex_unlock(&philo->program->eaten_lock);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
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
