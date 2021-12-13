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

int64_t	gettime_ms()
{
	t_time	tv;
	double	time_in_mill;

	gettimeofday(&tv, NULL);
	time_in_mill =(int64_t)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (time_in_mill);
}

void	test(t_env *env, int64_t philo_number)
{
	if (philo_number == env->num_of_philos && env->state[philo_number] == HUNGRY
		&& env->state[1] != EATING && env->state[philo_number - 1] != EATING)
		env->state[philo_number] = EATING;
	else if (env->state[philo_number] == HUNGRY && env->state[philo_number + 1]
		!= EATING && env->state[philo_number - 1] != EATING)
		env->state[philo_number] = EATING;
}

void	put_forks(t_env *env, int64_t philo_number)
{
//	mutex	put_forks;
//
//	pthread_mutex_init(&put_forks, NULL);
//	pthread_mutex_lock(&put_forks);
	env->state[philo_number] = THINKING;
	test(env, philo_number - 1);
	test(env, philo_number + 1);
//	pthread_mutex_unlock(&put_forks);
	pthread_mutex_unlock(&((env->fork)[philo_number]));
	if (philo_number == env->num_of_philos)
		pthread_mutex_unlock(&((env->fork)[1]));
	else
		pthread_mutex_unlock(&((env->fork)[philo_number + 1]));
}

void	take_forks(t_env *env, int64_t philo_number)
{
//	mutex	forks;
//
//	pthread_mutex_init(&forks, NULL);
//	pthread_mutex_lock(&forks);
	env->state[philo_number] = HUNGRY;
	test(env, philo_number);
//	pthread_mutex_unlock(&forks);
	pthread_mutex_lock(&((env->fork)[philo_number]));
	printf("%lld %lld" FORK "\n", env->timestamp, philo_number);
	if (philo_number == env->num_of_philos)
		pthread_mutex_lock(&((env->fork)[1]));
	else
		pthread_mutex_lock(&((env->fork)[philo_number + 1]));
	printf("%lld %lld" FORK "\n", env->timestamp, philo_number);
}

void	*philo_alive(void *args)
{
	t_env	*env;

	env = (t_env *)args;
	while (21)
	{
		printf("%lld\n", env->phil_n);
		printf("%lld %lld" THINK "\n", env->timestamp, env->phil_n);
		take_forks(env, env->phil_n);
		if (env->state[env->phil_n] == EATING)
		{
			env->timestamp = env->timestamp + env->time_to_eat;
			printf("%lld %lld" EAT "\n", env->timestamp, env->phil_n);
			usleep(env->time_to_eat);
		}
		put_forks(env, env->phil_n);
		env->timestamp = env->timestamp + env->time_to_eat;
		printf("%lld %lld" SLEEP "\n", env->timestamp, env->phil_n);
		usleep(env->time_to_sleep);
		if (env->phil_n == env->num_of_philos)
			env->phil_n = 1;
		else
			env->phil_n++;
		usleep(100000);
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	philo[PHILO_MAX];
	int64_t		i;
//	int64_t		time_in_mill;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_mutex_init(&(env->fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		printf("%lld\n", env->phil_n);
		env->phil_n = i + 1;
		pthread_create(&philo[i], NULL, &philo_alive, (void *) env);
		i++;
	}
	while (21)
	{
		if (env->timestamp > env->time_to_die)
		{
			printf("%lld %lld" DEATH "\n", env->timestamp, env->phil_n);
			while (i < env->num_of_philos)
			{
				pthread_detach(philo[i]);
				i++;
			}
			return(0);
		}
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_join(philo[i], NULL);
		i++;
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

	check_argv(argc, argv);
	init_data(&env, argc, argv);
	threads(&env);
	return (0);
}
