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
	t_env		*env;
	uint32_t	i;
	int			k;
	int64_t		time_ms;

	env = (t_env *)args;
	i = 0;
	k = 0;
	while (21)
	{
		i = 0;
		while (i < env->num_of_philos)
		{
			time_ms = get_time_ms();
//			printf("time_ms in mon = %lld\n", time_ms);
			if (time_ms - env->time_to_die > env->philosopher[i].timestamp)
			{
				env->philosopher[i].is_dead = 1;
				printf("%lld %lld" DEATH "\n", env->philosopher[i].timestamp,
					env->philosopher[i].id);
				return (NULL);
			}
			i++;
		}
	}
}

void	*philo_alive(void *args)
{
	t_philo		*philo;
	int64_t	time;

	philo = (t_philo*)args;
	philo->timestamp = get_time_ms();
	time = philo->timestamp;
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
//		philo->timestamp = get_time_ms();
		printf("%lld %lld" EAT "\n", philo->timestamp, philo->id);
		philo->timestamp = philo->timestamp + philo->env->time_to_eat;
		usleep(philo->env->time_to_eat);
		philo->timestamp = get_time_ms();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %lld" SLEEP "\n", philo->timestamp, philo->id);
		usleep(philo->env->time_to_sleep);
		philo->timestamp = philo->timestamp + philo->env->time_to_sleep;
	}
	else
		usleep(1000);
	while (philo->is_dead == 0)
	{
//		printf("start\n");
//		printf("%lld\n", philo->id);
//		philo->timestamp = get_time_ms();
//		printf("time_to_eat = %lld\n", philo->env->time_to_eat);
//		printf("time_to_sleep = %lld\n", philo->env->time_to_sleep);
//		printf("time_to_die = %lld\n", philo->env->time_to_die);
		printf("%lld %lld" THINK "\n", philo->timestamp, philo->id);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		time = get_time_ms();
		printf("%lld %lld" EAT "\n", time, philo->id);
		time = time + philo->env->time_to_eat;
		time = get_time_ms();
//		printf("time before usleep: %lld\n", time);
		usleep(philo->env->time_to_eat * 1000);
		time = get_time_ms();
//		printf("time after usleep:  %lld\n", time);
		philo->timestamp = get_time_ms();
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
//		philo->timestamp = get_time_ms();
		printf("%lld %lld" SLEEP "\n", philo->timestamp, philo->id);
		usleep(philo->env->time_to_sleep * 1000);
		philo->timestamp = philo->timestamp + philo->env->time_to_sleep;
//		usleep(100000);
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
//		printf("test\n");
		pthread_mutex_init(&(env->fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
//		printf("test\n");
//		printf("philo[%lld] in init = %lld\n", i, (env->philosopher + i)->id);
		pthread_create(&(env->philo)[i], NULL, &philo_alive,
			(void *)(env->philosopher + i));
		i++;
	}
	pthread_create(&waiter, NULL, &monitor, (void *)env);
	pthread_join(waiter, NULL);
	return (0);
//	i = 0;
//	while (i < env->num_of_philos)
//	{
//		pthread_detach((env->philo)[i]);
//		i++;
//	}
//	usleep(100000000);
//	i = 0;
//	while (i < env->num_of_philos)
//	{
//		pthread_join((env->philo)[i], NULL);
//		i++;
//	}
//
//	i = 0;
//	while (i < env->num_of_philos)
//	{
//		pthread_mutex_destroy(&((env->fork)[i]));
//		i++;
//	}
//	return (0);
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
