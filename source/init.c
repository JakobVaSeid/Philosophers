/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:13:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/05 16:45:55 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

int	init_mutex(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nbr_philos)
	{
		pthread_mutex_init(&program->forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&program->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&program->eaten_lock, NULL))
		return (1);
	if (pthread_mutex_init(&program->dead_lock, NULL))
		return (1);
	return (0);
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
	program->nbr_philos = ft_atoi(argv[1]);
	program->tt_die = ft_atoi(argv[2]);
	program->tt_eat = ft_atoi(argv[3]);
	program->tt_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->meals = ft_atoi(argv[5]);
	else
		program->meals = -1;
	program->finished_eating = 0;
	return (0);
}

int	init(t_program *program, int argc, char **argv)
{
	if (!program)
		return (1);
	if (init_prgm(program, argc, argv))
		return (1);
	if (init_philo(program))
		return (1);
	if (init_mutex(program))
		return (1);
	return (0);
}
