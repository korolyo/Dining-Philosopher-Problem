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
	t_philo	*philo;

	philo = (t_philo*)args;
	while (21)
	{
		printf("start\n");
//		printf("%lld\n", philo->id);
		printf("%lld %lld" THINK "\n", philo->timestamp, philo->id);
		if (philo->state == EATING)
		{
			philo->timestamp = philo->timestamp + philo->env->time_to_eat;
			printf("%lld %lld" EAT "\n", philo->timestamp, philo->id);
			usleep(philo->env->time_to_eat);
		}
		philo->timestamp = philo->timestamp + 0;
		printf("%lld %lld" SLEEP "\n", philo->timestamp, philo->id);
		usleep(philo->env->time_to_sleep);
//		usleep(100000);
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	philo[PHILO_MAX];
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
		printf("philo[%lld] in init = %lld\n", i, (env->philosopher + i)->id);
		pthread_create(&philo[i], NULL, &philo_alive,
			(void *)(env->philosopher + i));
		i++;
	}
	usleep(100000000);
	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
		printf("end\n");
	}

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_destroy(&((env->fork)[i]));
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!check_argv(argc, argv))
		return (0);
	if (init_data(&env, argc, argv) == -1)
	{
		printf(ERROR);
		return (0);
	}
	threads(&env);
	return (0);
}
