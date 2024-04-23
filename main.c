/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:37:14 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/23 17:00:59 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

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

int check_args(int argc, char **argv)
{
    int i;

    i = 1;
    /* if (is_number(argv[1] && argv[1] > 200))
        return (0); */
    while (i < argc)
    {
        if(argv[i][0] == '-')
            i++;
        if (!is_number(argv[i]))
            return (0);
        i++;
    }
    return (1);
}

int main (int argc, char **argv)
{
    if(argc > 5 || argc < 4)
        return (1);
    if(!check_args(argc, argv))
        return (1);
    
    return (0);
}