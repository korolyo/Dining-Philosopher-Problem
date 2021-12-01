#include "philo.h"

void	*philo_alive(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	printf("Time to eat: %lld\n", philo->time_to_eat);
	if (philo->time_to_die < philo->time_to_eat + philo->time_to_sleep)
		printf("I'm DEAD!\n");
	return (SUCCESS);
}

void threads(t_philo *philo)
{
	pthread_t	threads[philo->number_of_philosophers];
	int			i;
	int 		status;
	int 		status_addr;

	i = 0;
	status = pthread_create(&threads, NULL, philo_alive, (void *)&philo);
	if (status != 0)
	{
		printf("main error: can't CREATE thread, status = %d\n", status);
		exit(ERROR_CREATE_THREAD);
	}
	usleep(300000);
	printf(ANSI_COLOR_RED "Inside of a main"		ANSI_COLOR_RESET"\n");
	status = pthread_join(threads, (void **)&status_addr);
	if (status != SUCCESS)
	{
		printf("main error: cant JOIN thread, status %d\n", status);
		exit(ERROR_JOIN_THREAD);
	}
	printf(ANSI_COLOR_MAGENTA"joined with address %d\n"ANSI_COLOR_MAGENTA, status_addr);
}

int	main(int argc, char **argv)
{
	t_philo		philo;

	init_data(&philo);
	check_argv(&philo, argc, argv);
	threads(&philo);
	return (0);
}
