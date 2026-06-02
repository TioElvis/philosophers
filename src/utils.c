#include "philosophers.h"

long gettimeofday_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void delay(long ms)
{
	long start_time;

	start_time = gettimeofday_ms();
	while (gettimeofday_ms() - start_time < ms)
		usleep(100);
}

void print_state(t_philo *philo, const char *state)
{
	long timestamp;

	pthread_mutex_lock(&philo->table->display);
	timestamp = gettimeofday_ms() - philo->table->start_time;
	if (is_finished_dinner(philo->table) == TRUE)
	{
		pthread_mutex_unlock(&philo->table->display);
		return;
	}
	printf("%ld %d %s\n", timestamp, philo->id, state);
	pthread_mutex_unlock(&philo->table->display);
}

t_bool is_finished_dinner(t_table *table)
{
	t_bool result;

	pthread_mutex_lock(&table->monitor);
	result = table->is_finished;
	pthread_mutex_unlock(&table->monitor);
	return (result);
}
