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
//	int64_t		curr_time;

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
				printf("%lld %lld" DEATH "\n", time_ms - env->philosopher[i]
				.timestamp,
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
	int64_t		time;
	int64_t		curr_time;

	philo = (t_philo*)args;
	philo->timestamp = get_time_ms();
	time = 0;
	if (philo->id % 2 == 1)
	{
		printf("%lld %lld" FORK " left\n", time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %lld" FORK " right\n", time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %lld" EAT "\n", time, philo->id);
		ft_usleep(philo->env->time_to_eat);
		time = time + philo->env->time_to_eat;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %lld" SLEEP "\n", time, philo->id);
		ft_usleep(philo->env->time_to_sleep);
		time = time + philo->env->time_to_sleep;
	}
	else
		ft_usleep(10);
	while (philo->is_dead == 0)
	{
		printf("%lld %lld" THINK "\n", time, philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%lld %lld" FORK " left\n", time, philo->id);
		pthread_mutex_lock(philo->right_fork);
		curr_time = get_time_ms();
		time = time + curr_time - philo->timestamp;
		printf("%lld %lld" FORK " right\n", time, philo->id);
		printf("%lld %lld" EAT "\n", time, philo->id);
		philo->timestamp = get_time_ms();
//		printf("time before usleep: %lld\n", time);
		ft_usleep(philo->env->time_to_eat);
		time = time + philo->env->time_to_eat;
//		printf("time after usleep:  %lld\n", time);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		printf("%lld %lld" SLEEP "\n", time, philo->id);
		ft_usleep(philo->env->time_to_sleep);
		time = time + philo->env->time_to_sleep;
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
