/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2028/08/23 10:55:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/04/23 14:57:42 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//# include "philosphers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
    for (int i = 0; i < 10000000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
    }
   // read mails    |23|23
   // increment     |23|
   // write mails   |28|25
}

int main (int argc, char **argv)
{
    pthread_t th[8];
    pthread_mutex_init(&mutex, NULL);

    int i;

    for (i = 0; i < 8; i++)
    {
        if(pthread_create(&th[i], NULL, &routine, NULL) != 0)
        {
            perror("Failed to create thread");
            return (1);
        }
        printf("Thread %d has started \n", i);
    }
    for (i = 0; i < 8; i++)
    {
        if(pthread_join(th[i], NULL) != 0)
            return (2);
        printf("Thread %d has finished execution \n", i);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails %d\n", mails);
    return 0;
}





/* void *computation(void *add);

int main ()
{
    pthread_t thread1;
    pthread_t thread2;

    long value1 = 1;
    long value2 = 2;

    //computation( (void *) &value1);
    //computation( (void *) &value2);
    
    pthread_create(&thread1, NULL, computation, (void *) &value1);
    pthread_join(thread1, NULL); // this function w8s until thread1 is done 
                                // makes it less effective
    
    pthread_create(&thread2, NULL, computation, (void *) &value2);
    pthread_join(thread2, NULL);

    return (0);
}

void *computation(void *add)
{
    long *add_num = (long *) (add);
    long sum = 0;

    for (long i = 0; i < 1000000; i++)
        sum += *add_num;
    return (NULL);
} */