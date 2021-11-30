#include "philo.h"

void	check_argv(t_philo *philo, int argc, char **argv)
{
	if (argc < 5)
		printf("Error\n");
	else
	{
		philo->number_of_philosophers = ft_atol(argv[1]);
		philo->time_to_die = ft_atol(argv[2]);
		philo->time_to_eat = ft_atol(argv[3]);
		philo->time_to_sleep = ft_atol(argv[4]);
	}
}

void init_data(t_philo *philo)
{
	philo->left_hand = 0;
	philo->right_hand = 0;
	philo->number_of_philosophers = 0;
	philo->time_to_die = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
}
