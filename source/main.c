/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:14 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/01 14:21:35 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

//check if the string is a number
int is_number(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

//check if the arguments are valid
int check_args(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if(argv[i][0] == '0')
        {
            printf("Input cannot be 0\n");
            return (0);
        }
        if(argv[i][0] == '-')
        {
            printf("Input cannot be negative\n");
            return (0);
        }
        if(argv[i][0] == '+')
            i++;
        if (!is_number(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

void start_threads(t_program *program)
{
    int i = 0;
    pthread_t   control_thread;
    
    pthread_create(&control_thread, NULL, check_if_dead, program->philo);
    while(i < program->nbr_philos)
    {
        if(pthread_create(&program->philo[i].id_thread, NULL, routine, &program->philo[i]) != 0)
        {
            perror("Failed to create thread");
            return ;
        }
        printf("Thread %d has started \n", i);
        i++;
    }
    i = 0;
    while(i < program->nbr_philos)
    {
        if(pthread_join(program->philo[i].id_thread, NULL) != 0)
            return ;
        printf("Thread %d has finished execution \n", i);
        i++;
    }
}


int main(int argc, char **argv)
{   
    t_program   *program;
    //pthread_t   control_thread;
    //pthread_mutex_t mutex;
    
    program = malloc(sizeof(t_program));
    program->start_time = gettime();

    if(argc > 6 || argc < 5)
    {
        printf("Number of arguments is invalid\n");
        return (1);
    }
    if(!check_args(argc, argv))
        return (1);
    if(init(program, argc, argv))
        return (1);
    start_threads(program);
    //pthread_create(&control_thread, NULL, check_if_dead, program->philo);
    printf("Program initialized\n");
    return (0);
}

//Philos can die while eating
//Each Philo needs to be a thread | even one
//Own usleep function || monitoring function
