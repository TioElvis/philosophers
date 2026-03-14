/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:23:36 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:25:42 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	validate_arg(char *arg)
{
	int		i;
	long	number;

	i = 0;
	number = 0;
	if (arg[i] == '-')
		return (ERROR);
	if (arg[i] == '+')
		i++;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (ERROR);
		number = ft_atol(arg);
		if (number > INT_MAX)
			return (ERROR);
		i++;
	}
	if (number == 0)
		return (ERROR);
	return (SUCCESS);
}

static t_bool	is_valid_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (validate_arg(argv[i]) == ERROR)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	print_usage(void)
{
	printf("Error: Invalid arguments.\n\n");
	printf("Usage: ./philo number_of_philosophers");
	printf(" time_to_die time_to_eat time_to_sleep [number_of_meals]\n");
	printf("All arguments must be positive integers");
	printf(" greater than 0 and within the range of an int.\n");
}

int	initialize_args(t_args *args, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (print_usage(), ERROR);
	if (is_valid_args(argc, argv) == FALSE)
		return (print_usage(), ERROR);
	args->number_of_philos = (int)ft_atol(argv[1]);
	args->time_to_die = (int)ft_atol(argv[2]);
	args->time_to_eat = (int)ft_atol(argv[3]);
	args->time_to_sleep = (int)ft_atol(argv[4]);
	if (argc == 6)
		args->number_of_meals = (int)ft_atol(argv[5]);
	else
		args->number_of_meals = -1;
	return (SUCCESS);
}
