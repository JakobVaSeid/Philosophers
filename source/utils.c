/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/04 16:22:40 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

//convert a string to an integer
int	ft_atoi(const char *str)
{
	int	counter;
	int	number;

	counter = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		counter = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (number * counter);
}

long long	gettime(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

bool	is_dead(t_program *program)
{
	pthread_mutex_lock(&program->dead_lock);
	if (program->one_is_dead)
	{
		pthread_mutex_unlock(&program->dead_lock);
		return (true);
	}
	pthread_mutex_unlock(&program->dead_lock);
	return (false);
}

bool	time_dead(t_program *program)
{
	pthread_mutex_lock(&program->eaten_lock);
	if (gettime() - program->philo->last_meal > program->tt_die)
	{
		pthread_mutex_unlock(&program->eaten_lock);
		return (true);
	}
	pthread_mutex_unlock(&program->eaten_lock);
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

int	my_usleep(long long time, t_program *program)
{
	long long	start;

	start = gettime();
	while (!is_dead(program))
	{
		if (gettime() - start >= time)
			return (1);
		if (time_dead(program))
		{
			my_print(program->philo, "died\n");
			pthread_mutex_lock(&program->dead_lock);
			program->one_is_dead = true;
			pthread_mutex_unlock(&program->dead_lock);
			break ;
		}
		usleep(100);
	}
	return (0);
}

void	my_print(t_philo *phil, char *str)
{
	if (!is_dead(phil->program))
	{
		pthread_mutex_lock(&phil->program->write_lock);
		printf("%lld %d %s", gettime() - phil->program->start_time, \
		phil->id, str);
		pthread_mutex_unlock(&phil->program->write_lock);
	}
}

void	free_all(t_program *program)
{
	int	i;

	i = 0;
	if (program->philo)
	{
		while (i < program->nbr_philos)
		{
			pthread_mutex_destroy(&program->forks[i]);
			i++;
		}
		free(program->philo);
	}
	if (program->forks)
		free(program->forks);
	free(program);
}

//Deadlock