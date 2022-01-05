/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:10 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:08:22 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_alive(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->start_time = get_time_ms();
	philo->timestamp = philo->start_time;
	if (philo->id % 2 == 1)
		ft_usleep(10);
	while (philo->is_dead == 0)
	{
		take_forks(philo);
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	waiter;
	int64_t		i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_init(&(env->fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_create(&(env->philo)[i], NULL, &philo_alive,
			(void *)(env->philosopher + i));
		i++;
	}
	pthread_create(&waiter, NULL, &monitor, (void *)env->philosopher);
	pthread_join(waiter, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!check_argv(argc, argv))
		return (0);
	if (init_data(&env, argc, argv) == -1)
	{
		printf(ERROR_MESSAGE);
		return (0);
	}
	threads(&env);
//	clean_all(&env);
	return (0);
}
