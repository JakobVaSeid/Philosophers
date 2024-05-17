/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:14 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 21:09:42 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

//Function for looping through death
int	death_philo_check(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->nbr_philos)
	{
		if (time_dead(&program->philo[i]))
			return (1);
		i++;
	}
	return (0);
}

int	eat_philo_check(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < program->nbr_philos)
	{
		if (one_eaten(&program->philo[i]))
			j++;
		i++;
	}
	if (j == program->nbr_philos)
		return (1);
	return (0);
}

//check if philo is dead
void	monitoring(t_program *program)
{
	while (!is_dead(program->philo) && !finished_eating(program->philo))
	{
		if (death_philo_check(program))
		{
			pthread_mutex_lock(&program->dead_lock);
			program->one_is_dead = true;
			pthread_mutex_unlock(&program->dead_lock);
		}
		if (eat_philo_check(program))
		{
			pthread_mutex_lock(&program->eaten_lock);
			program->finished_eating = true;
			pthread_mutex_unlock(&program->eaten_lock);
		}
		usleep(500);
	}
}

int	start_threads(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = gettime();
	while (i < program->nbr_philos)
	{
		if (pthread_create(&program->philo[i].id_thread, NULL, \
		routine, &program->philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			ft_pthread_join(program, i);
			break ;
		}
		pthread_mutex_lock(&program->eaten_lock);
		program->philo[i].last_meal = gettime();
		pthread_mutex_unlock(&program->eaten_lock);
		i++;
	}
	monitoring(program);
	if (ft_pthread_join(program, i))
	{
		ft_putstr_fd("Error joining thread\n", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	*program;

	if (argc > 6 || argc < 5)
	{
		ft_putstr_fd("Number of arguments is invalid\n", 2);
		return (1);
	}
	if (!check_args(argc, argv))
		return (1);
	program = malloc(sizeof(t_program));
	if (!program)
	{
		ft_putstr_fd("Error: Malloc Program failed\n", 2);
		return (1);
	}
	if (init(program, argc, argv))
		return (1);
	if (start_threads(program))
	{
		printf("Error creating thread\n");
		return (1);
	}
	destroy_mutex(program);
	free_all(program);
	return (0);
}
