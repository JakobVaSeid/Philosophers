/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/01 14:56:17 by jseidere         ###   ########.fr       */
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

long long gettime()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int my_usleep(long long time)
{
	long long start;

	start = gettime();
	while (gettime() - start < time)
		usleep(100);
	return (0);
}

void *check_if_dead(void *philo)
{
	t_philo *phil = (t_philo *)philo;
	while(!phil->program->finished_eating)
	{
		printf("Death_check_finished_eating\n");
		//printf("One_is_dead: %d\n", phil->program->one_is_dead);
		while(!phil->program->one_is_dead)
		{
			if (gettime() - phil->last_meal > phil->program->tt_die)
			{
				pthread_mutex_lock(phil->write_lock);
				printf("%lld %d died\n", gettime() - phil->program->start_time, phil->id);
				phil->is_dead = true;
				pthread_mutex_unlock(phil->write_lock);
			}
		}
		if(phil->program->one_is_dead)
			return (NULL);
	}
	return (NULL);
}
