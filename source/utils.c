/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:01:06 by jseidere          #+#    #+#             */
/*   Updated: 2024/05/10 21:20:31 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosphers.h"

//convert a string to an long long
long long	ft_atol(const char *str)
{
	int			counter;
	long long	number;

	counter = 1;
	number = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		counter = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (number * counter);
}

long long	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//check if the string is a number
int	is_number(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_plus_minus(char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '+')
			j++;
		if (str[i] == '-')
			k++;
		i++;
	}
	if (j > 1 || k > 1)
		return (1);
	return (0);
}

//check if the arguments are valid
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (check_plus_minus(argv[i]))
		{
			ft_putstr_fd("Input is invalid\n", 2);
			return (0);
		}
		if (ft_atol(argv[i]) == 0)
		{
			ft_putstr_fd("Input cannot be 0\n", 2);
			return (0);
		}
		if (!is_number(argv[i]))
		{
			ft_putstr_fd("Input is not valid\n", 2);
			return (0);
		}
		if (check_max(ft_atol(argv[i])))
			return (0);
		i++;
	}
	return (1);
}
