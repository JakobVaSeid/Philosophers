/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/05 17:14:54 by jseidere         ###   ########.fr       */
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
