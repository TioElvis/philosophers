/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:23:42 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:26:35 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*initialize_philos(t_table *table)
{
	t_philo	*philos;
	int		i;
	int		number_of_philos;

	number_of_philos = table->args.number_of_philos;
	philos = malloc(sizeof(t_philo) * number_of_philos);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].table = table;
		philos[i].state = THINKING;
		philos[i].left_fork = &table->forks[i];
		philos[i].right_fork = &table->forks[(i + 1) % number_of_philos];
		philos[i].last_meal_time = 0;
		philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&philos[i].meal, NULL) != 0
			|| pthread_mutex_init(&philos[i].sleep, NULL) != 0)
			return (NULL);
		philos[i].last_sleep_time = 0;
		i++;
	}
	return (philos);
}

static pthread_mutex_t	*initialize_forks(int number_of_philos)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * number_of_philos);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (forks);
}

t_table	*initialize_table(t_args args)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->args = args;
	table->start_time = gettimeofday_ms();
	if (pthread_mutex_init(&table->display, NULL) != 0)
		return (NULL);
	if (pthread_mutex_init(&table->monitor, NULL) != 0)
		return (NULL);
	table->is_finished = FALSE;
	table->forks = initialize_forks(args.number_of_philos);
	if (!table->forks)
		return (NULL);
	table->philos = initialize_philos(table);
	if (!table->philos)
		return (NULL);
	return (table);
}
