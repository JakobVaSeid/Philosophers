/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:59:34 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/23 15:18:08 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *roll_dice()
{
    int value = (rand() % 6) + 1;
    int *result = malloc(sizeof(int));
    *result = value; 
    //printf("Thread result: %p\n", result);
    return ((void *) result);
}

int main(int argc, char **argv)
{
    int *result;
    int i = 0;
    result = NULL;
    srand(time(NULL));
    pthread_t th[8];

    while(i < 8)
    {
        if(pthread_create(th + i, NULL, &roll_dice, NULL) != 0)
            return (1);
        i++;
    }
    i = 0;
    while(i < 8)
    {    
        if(pthread_join(th[i], (void **) &result) != 0)
            return (2);
        printf("Result[%d]: %d\n", i, *result);
        i++;
    }
    free(result);
    return (0);
}