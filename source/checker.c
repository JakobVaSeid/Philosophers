/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:03:44 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/05 18:40:40 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->dead_lock);
	if (philo->program->one_is_dead)
	{
		pthread_mutex_unlock(&philo->program->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->program->dead_lock);
	return (false);
}

bool	time_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->eaten_lock);
	if (gettime() - philo->last_meal >= philo->program->tt_die)
	{
		my_print(philo, "died\n");
		pthread_mutex_lock(&philo->program->dead_lock);
		philo->program->one_is_dead = true;
		pthread_mutex_unlock(&philo->program->dead_lock);
		pthread_mutex_unlock(&philo->program->eaten_lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->program->eaten_lock);
	return (false);
}

bool	finished_eating(t_program *program)
{
	pthread_mutex_lock(&program->eaten_lock);
	if (program->finished_eating)
	{
		pthread_mutex_unlock(&program->eaten_lock);
		return (true);
	}
	pthread_mutex_unlock(&program->eaten_lock);
	return (false);
}

bool	all_eaten(t_program *program)
{
	pthread_mutex_lock(&program->eaten_lock);
	if (program->philo->meals_eaten <= program->meals || program->meals == -1)
	{
		pthread_mutex_unlock(&program->eaten_lock);
		return (false);
	}
	pthread_mutex_unlock(&program->eaten_lock);
	return (true);
}
