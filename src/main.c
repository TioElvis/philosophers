#include "philosophers.h"

int main(int argc, char **argv)
{
	t_args args;
	t_table *table;

	if (initialize_args(&args, argc, argv) == ERROR)
		return (ERROR);
	table = initialize_table(args);
	if (!table)
		return (cleanup(table), ERROR);
	if (start_dinner(table) == ERROR)
		return (cleanup(table), ERROR);
	return (cleanup(table), SUCCESS);
}
