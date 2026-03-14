/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:24:18 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:24:18 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->args.number_of_philos == 1)
		return (eating(philo), NULL);
	if (philo->id % 2 == 0)
		delay(10);
	while (is_finished_dinner(philo->table) == FALSE)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	start_dinner(t_table *table)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, monitor_routine, table) != 0)
		return (ERROR);
	i = 0;
	while (i < table->args.number_of_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&table->philos[i]) != 0)
			return (ERROR);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < table->args.number_of_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	return (SUCCESS);
}
