#include "philo.h"

void	check_argv(t_philo *philos, int argc, char **argv)
{
	if (argc < 5)
		printf("Error\n");
	else
	{
		philos->number_of_philosophers = ft_atol(argv[1]);
		philos->time_to_die = ft_atol(argv[2]);
		philos->time_to_eat = ft_atol(argv[3]);
		philos->time_to_sleep = ft_atol(argv[4]);
	}
}

void init_data(t_philo *philos)
{
	philos->left_hand = 0;
	philos->right_hand = 0;
	philos->number_of_philosophers = 0;
	philos->time_to_die = 0;
	philos->time_to_eat = 0;
	philos->time_to_sleep = 0;
}
