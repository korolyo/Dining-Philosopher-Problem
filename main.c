#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philo;
//	pthread_t	thread[1];
	int64_t		i;

	i = 0;
	philo = NULL;
	init_data(philo);
	check_argv(philo, argc, argv);
	i = philo->number_of_philosophers;
	while (i > 0)
//		pthread_create(&thread[i], NULL, 1, NULL);
	return (0);
}
