/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:24:13 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:24:13 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	thinking(t_philo *philo)
{
	if (is_finished_dinner(philo->table) == TRUE)
		return ;
	print_state(philo, "is thinking");
	philo->state = THINKING;
	delay(1);
}

static int	take_forks_odd(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken fork");
	if (philo->table->args.number_of_philos == 1)
		return (pthread_mutex_unlock(philo->right_fork), ERROR);
	if (is_finished_dinner(philo->table) == TRUE)
		return (pthread_mutex_unlock(philo->right_fork), ERROR);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken fork");
	if (is_finished_dinner(philo->table) == TRUE)
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), ERROR);
	return (SUCCESS);
}

static int	take_forks_even(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(philo, "has taken fork");
	if (philo->table->args.number_of_philos == 1)
		return (pthread_mutex_unlock(philo->left_fork), ERROR);
	if (is_finished_dinner(philo->table) == TRUE)
		return (pthread_mutex_unlock(philo->left_fork), ERROR);
	pthread_mutex_lock(philo->right_fork);
	print_state(philo, "has taken fork");
	if (is_finished_dinner(philo->table) == TRUE)
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), ERROR);
	return (SUCCESS);
}

void	eating(t_philo *philo)
{
	if (is_finished_dinner(philo->table) == TRUE)
		return ;
	if (philo->id % 2 == 0)
	{
		if (take_forks_even(philo) == ERROR)
			return ;
	}
	else
	{
		if (take_forks_odd(philo) == ERROR)
			return ;
	}
	print_state(philo, "is eating");
	philo->state = EATING;
	pthread_mutex_lock(&philo->meal);
	philo->last_meal_time = gettimeofday_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	delay(philo->table->args.time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleeping(t_philo *philo)
{
	if (is_finished_dinner(philo->table) == TRUE)
		return ;
	print_state(philo, "is sleeping");
	philo->state = SLEEPING;
	pthread_mutex_lock(&philo->sleep);
	philo->last_sleep_time = gettimeofday_ms();
	pthread_mutex_unlock(&philo->sleep);
	delay(philo->table->args.time_to_sleep);
}
