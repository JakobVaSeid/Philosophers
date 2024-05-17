/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosphers.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:55:26 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 20:17:50 by jseidere         ###   ########.fr       */
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
	int				created_philos;
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
	bool			*is_dead;
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
int			init_mutex2(t_program *program);

//utils.c
long long	ft_atol(const char *str);
long long	gettime(void);
void		free_all(t_program *program);
int			check_args(int argc, char **argv);

//to_dos.c
int			ft_sleep(t_philo *philo);
int			ft_think(t_philo *philo);
int			ft_eat_even(t_philo *philo);
int			ft_eat_uneven(t_philo *philo);
int			ft_eat(t_philo *philo);

//routine.c
void		my_print(t_philo *phil, char *str);
int			time_shift(t_philo *philo);
int			my_usleep(long long time, t_philo *philo);
void		*routine(void *philo);

//checker.c
bool		is_dead(t_philo *philo);
bool		finished_eating(t_philo *philo);
bool		one_eaten(t_philo *philo);
bool		time_dead(t_philo *philo);
bool		all_eaten(t_program *program);

//free.c
void		free_all(t_program *program);
long long	check_max(long long num);
int			ft_putstr_fd(char *s, int fd);
int			ft_pthread_join(t_program *program, int i);

//new 
void		monitoring(t_program *prg);
int			death_philo_check(t_program *program);