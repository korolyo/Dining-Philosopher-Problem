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

void	*monitor(void *args)
{
	t_env	*env;
	int		i;
	int64_t	time_ms;

	env = (t_env *)args;
	while (21)
	{
		i = 0;
		while (i < env->num_of_philos)
		{
			time_ms = get_time_ms();
			if (get_time_ms() - env->time_to_die > env->philosopher[i].timestamp)
				printf("%lld %lld" DEATH "\n", env->philosopher[i].timestamp,
					   env->philosopher[i].id);
			i++;
		}
	}
}

void	*philo_alive(void *args)
{
	t_philo	*philo;

	philo = (t_philo*)args;
	while (21)
	{
//		printf("start\n");
//		printf("%lld\n", philo->id);
		philo->timestamp = get_time_ms();
		printf("%lld %lld" THINK "\n", philo->timestamp, philo->id);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
		if (philo->state == EATING)
		{
			philo->timestamp = philo->timestamp + philo->env->time_to_eat;
			printf("%lld %lld" EAT "\n", philo->timestamp, philo->id);
			philo->timestamp = get_time_ms();
			usleep(philo->env->time_to_eat);
		}
		philo->timestamp = get_time_ms();
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		printf("%lld %lld" SLEEP "\n", philo->timestamp, philo->id);
		usleep(philo->env->time_to_sleep);
//		usleep(100000);
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	philo[PHILO_MAX];
	pthread_t	waiter;
	int64_t		i;

	i = 0;
	while (i < env->num_of_philos)
	{
//		printf("test\n");
		pthread_mutex_init(&(env->fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
//		printf("test\n");
//		printf("philo[%lld] in init = %lld\n", i, (env->philosopher + i)->id);
		pthread_create(&philo[i], NULL, &philo_alive,
			(void *)(env->philosopher + i));
		i++;
	}
	pthread_create(&waiter, NULL, &monitor, (void *)env);
	usleep(100000000);
	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
//		printf("end\n");
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
