/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evera <evera@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 13:24:04 by evera             #+#    #+#             */
/*   Updated: 2026/02/07 13:24:07 by evera            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ========== LIBRARIES ========== */
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

/* ========== DEFINES ========== */
# define ERROR 1
# define SUCCESS 0

/* ========== STRUCTURES ========== */
typedef enum e_bool
{
	TRUE,
	FALSE,
}					t_bool;

typedef enum e_state
{
	DEAD,
	EATING,
	THINKING,
	SLEEPING
}					t_state;

typedef struct s_philo
{
	t_state			state;
	pthread_t		thread;
	pthread_mutex_t	meal;
	pthread_mutex_t	sleep;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	long			last_sleep_time;
}					t_philo;

typedef struct s_args
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				number_of_philos;
}					t_args;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	display;
	pthread_mutex_t	monitor;
	t_args			args;
	t_philo			*philos;
	t_bool			is_finished;
	long			start_time;
}					t_table;

/* ========== FUNCTIONS ========== */
int					initialize_args(t_args *args, int argc, char **argv);

t_table				*initialize_table(t_args args);

void				cleanup(t_table *table);

int					start_dinner(t_table *table);

void				thinking(t_philo *philo);
void				eating(t_philo *philo);
void				sleeping(t_philo *philo);

long				gettimeofday_ms(void);
void				delay(long ms);
void				print_state(t_philo *philo, const char *state);

t_bool				is_finished_dinner(t_table *table);
void				*monitor_routine(void *arg);
#endif