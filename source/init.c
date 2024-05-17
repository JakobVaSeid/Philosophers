/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:13:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 18:22:13 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int	init_mutex(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nbr_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&program->forks[i]);
				i--;
			}
			return (1);
		}
		i++;
	}
	init_mutex2(program);
	return (0);
}

int	init_mutex2(t_program *program)
{
	if (pthread_mutex_init(&program->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&program->eaten_lock, NULL))
	{
		pthread_mutex_destroy(&program->write_lock);
		return (1);
	}
	if (pthread_mutex_init(&program->dead_lock, NULL))
	{
		pthread_mutex_destroy(&program->write_lock);
		pthread_mutex_destroy(&program->eaten_lock);
		return (1);
	}
	return (0);
}

//create the philosphers
int	init_philo(t_program *program)
{
	int	i;

	i = 0;
	program->philo = malloc(sizeof(t_philo) * program->nbr_philos);
	if (!program->philo)
		return (1);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->nbr_philos);
	if (!program->forks)
		return (free(program->philo), 1);
	while (i < program->nbr_philos)
	{
		program->philo[i].id = i + 1;
		program->philo[i].id_thread = i;
		program->philo[i].fork_r = &program->forks[i];
		program->philo[i].fork_l = &program->forks[(i + 1) % \
			program->nbr_philos];
		program->philo[i].last_meal = 0;
		program->philo[i].program = program;
		program->philo[i].program->one_is_dead = false;
		program->philo[i].is_dead = &program->one_is_dead;
		if (program->meals)
			program->philo[i].meals_eaten = 0;
		i++;
	}
	return (0);
}

//initialize the program
int	init_prgm(t_program *program, int argc, char **argv)
{
	if (!program)
		return (1);
	program->nbr_philos = ft_atol(argv[1]);
	program->tt_die = ft_atol(argv[2]);
	program->tt_eat = ft_atol(argv[3]);
	program->tt_sleep = ft_atol(argv[4]);
	if (argc == 6)
		program->meals = ft_atol(argv[5]);
	else
		program->meals = -1;
	program->finished_eating = 0;
	program->created_philos = 0;
	return (0);
}

int	init(t_program *program, int argc, char **argv)
{
	if (!program)
		return (1);
	if (init_prgm(program, argc, argv))
	{
		ft_putstr_fd("Error: Programm failed\n", 2);
		return (free(program), 1);
	}
	if (init_philo(program))
	{
		ft_putstr_fd("Error: Philo failed\n", 2);
		return (free(program), 1);
	}
	if (init_mutex(program))
	{
		ft_putstr_fd("Error: Mutex failed\n", 2);
		return (free(program), 1);
	}
	return (0);
}
