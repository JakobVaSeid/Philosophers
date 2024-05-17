/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:50:16 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 20:29:45 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

void	free_all(t_program *program)
{
	int	i;

	i = 0;
	if (program->philo)
	{
		free(program->philo);
	}
	if (program->forks)
		free(program->forks);
	free(program);
}

int	destroy_mutex(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nbr_philos)
	{
		pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->eaten_lock);
	pthread_mutex_destroy(&program->dead_lock);
	return (0);
}

int	ft_pthread_join(t_program *program, int i)
{
	while (i-- > 0)
	{
		if (pthread_join(program->philo[i].id_thread, NULL) != 0)
			return (1);
	}
	return (0);
}

//check for max int
long long	check_max(long long num)
{
	if (num > 2147483647)
	{
		ft_putstr_fd("Error: Number is too large\n", 2);
		return (1);
	}
	return (0);
}

//print str in fd
int	ft_putstr_fd(char *s, int fd)
{
	int		len;
	size_t	i;

	len = 0;
	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
		len++;
	}
	return (len);
}
