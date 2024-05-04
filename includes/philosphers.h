/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:55:26 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/04 16:32:00 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_program
{
	int				nbr_philos;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				finished_eating;
	bool			one_is_dead;
	int				meals;
	long long		start_time;
	pthread_mutex_t	eaten_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_program;

typedef struct s_philo
{
	pthread_t		id_thread;
	int				id;
	long long		last_meal;
	int				meals_eaten;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	t_program		*program;
}	t_philo;

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////source///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//init.c
int			init_mutex(t_program *program);
int			init_philo(t_program *program);
int			init_prgm(t_program *program, int argc, char **argv);
int			init(t_program *program, int argc, char **argv);
int			destroy_mutex(t_program *program);

//utils.c
int			ft_atoi(const char *str);
long long	gettime(void);
int			my_usleep(long long time, t_program *program);
void		free_all(t_program *program);
void		my_print(t_philo *phil, char *str);
bool		is_dead(t_program *program);
bool		finished_eating(t_program *program);
bool		all_eaten(t_program *program);
bool		time_dead(t_program *program);

//routine.c
int			ft_sleep(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat(t_philo *philo);
void		*routine(void *philo);
