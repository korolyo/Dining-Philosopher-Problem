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

#include "philo_bonus.h"

void	*philo_alive(t_philo *philo)
{
	philo->env->start_time = get_time_ms();
	philo->timestamp = philo->env->start_time;
	if (philo->id % 2 == 1)
		ft_usleep(10);
	while (1)
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
		env->philosopher[i].pid = fork();
		if (env->philosopher[i].pid == -1)
		{
			printf(ERROR_MESSAGE);
			exit(0);
		}
		if (env->philosopher[i].pid == 0)
		{
			pthread_create(&waiter, NULL, &monitor, (void *) env->philosopher);
			philo_alive(&env->philosopher[i]);
			pthread_join(waiter, NULL);
			exit(0);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!check_argv(argc, argv))
	{
		printf("Wrong args!\n");
		return (0);
	}
	if (init_data(&env, argc, argv) == -1)
	{
		printf("Error in init\n");
		return (0);
	}
	threads(&env);
	sem_wait(env.ending);
	clean_all(&env);
	return (0);
}
