#include "philosophers.h"

static void free_table(t_table *table)
{
	if (table != NULL)
	{
		if (table->philos != NULL)
			free(table->philos);
		if (table->forks != NULL)
			free(table->forks);
		free(table);
	}
}

static void destroy_mutexes(t_table *table)
{
	int i;

	if (table == NULL)
		return;
	pthread_mutex_destroy(&table->display);
	pthread_mutex_destroy(&table->monitor);
	if (table->forks != NULL)
	{
		i = 0;
		while (i < table->args.number_of_philos)
		{
			pthread_mutex_destroy(&table->forks[i]);
			i++;
		}
	}
	if (table->philos != NULL)
	{
		i = 0;
		while (i < table->args.number_of_philos)
		{
			pthread_mutex_destroy(&table->philos[i].meal);
			pthread_mutex_destroy(&table->philos[i].sleep);
			i++;
		}
	}
}

void cleanup(t_table *table)
{
	destroy_mutexes(table);
	free_table(table);
}
