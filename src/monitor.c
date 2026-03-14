/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:23:53 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:23:58 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	set_dead_philosopher(t_philo *philo)
{
	t_table	*table;
	long	current_time;

	table = philo->table;
	current_time = gettimeofday_ms() - table->start_time;
	pthread_mutex_lock(&philo->meal);
	pthread_mutex_lock(&philo->sleep);
	if (current_time - philo->last_meal_time > table->args.time_to_die
		|| current_time - philo->last_sleep_time > table->args.time_to_die)
	{
		philo->state = DEAD;
		print_state(philo, "died");
		pthread_mutex_lock(&table->monitor);
		table->is_finished = TRUE;
		pthread_mutex_unlock(&table->monitor);
		pthread_mutex_unlock(&philo->meal);
		pthread_mutex_unlock(&philo->sleep);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_unlock(&philo->sleep);
	return (FALSE);
}

static t_bool	all_philosophers_ate_enough(t_table *table)
{
	int	i;
	int	philos_finished;

	if (table->args.number_of_meals <= 0)
		return (FALSE);
	i = 0;
	philos_finished = 0;
	while (i < table->args.number_of_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal);
		if (table->philos[i].meals_eaten >= table->args.number_of_meals)
			philos_finished++;
		pthread_mutex_unlock(&table->philos[i].meal);
		i++;
	}
	if (philos_finished == table->args.number_of_philos)
		return (TRUE);
	return (FALSE);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_table	*table;
	t_philo	*philo;

	table = (t_table *)arg;
	while (is_finished_dinner(table) == FALSE)
	{
		i = 0;
		while (i < table->args.number_of_philos)
		{
			philo = &table->philos[i];
			if (set_dead_philosopher(philo) == TRUE)
				return (NULL);
			i++;
		}
		if (all_philosophers_ate_enough(table) == TRUE)
		{
			pthread_mutex_lock(&table->monitor);
			table->is_finished = TRUE;
			pthread_mutex_unlock(&table->monitor);
			return (NULL);
		}
		delay(1);
	}
	return (NULL);
}
