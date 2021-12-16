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

void	test(t_philo *philo)
{
	if (philo->id == philo->env->num_of_philos && philo->state ==
		HUNGRY && philo->state[1] != EATING && philo->state !=
		EATING)
		env->state[philo_number] = EATING;
	else if (env->state[philo_number] == HUNGRY && env->state[philo_number + 1]
		!= EATING && env->state[philo_number - 1] != EATING)
		env->state[philo_number] = EATING;
}

void	put_forks(t_philo *philo)
{
	philo->state = THINKING;
	test(philo);
	test(philo);
	pthread_mutex_unlock(&(philo->left_fork);
	if (philo_number == env->num_of_philos)
		pthread_mutex_unlock(&((philo->right)[1]));
	else
		pthread_mutex_unlock(&((philo->right)[philo->id + 1]));
}

void	take_forks(t_philo *philo)
{
	philo->state = HUNGRY;
	test(philo);
	pthread_mutex_lock(&(philo->left_fork));
//	pthread_mutex_lock(&(philo->right_fork));
	printf("%lld %lld" FORK "\n", philo->timestamp, philo->id);
	if (philo->id == philo->env->num_of_philos)
		pthread_mutex_lock(&((env->fork)[1]));
	else
		pthread_mutex_lock(&((env->fork)[philo_number + 1]));
	printf("%lld %lld" FORK "\n", env->timestamp, philo_number);
}

void	*philo_alive(void *args)
{
	t_philo	*philo;

	philo = (t_philo*)args;
	while (21)
	{
		printf("%lld\n", philo->id);
		printf("%lld %lld" THINK "\n", philo->timestamp, philo->id);
		take_forks(philo);
		if (philo->state == EATING)
		{
			philo->timestamp = philo->timestamp + philo->env->time_to_eat;
			printf("%lld %lld" EAT "\n", env->timestamp, philo->id);
			usleep(env->time_to_eat);
		}
		put_forks(env, env->phil_n);
		env->timestamp = env->timestamp + env->time_to_eat;
		printf("%lld %lld" SLEEP "\n", philo->timestamp, env->phil_n);
		usleep(philo->env->time_to_sleep);
		usleep(100000);
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
		env->philosopher[i]->id = i + 1;
		pthread_create(&philo[i], NULL, &philo_alive, (void *)
		env->philosopher[i]);
		i++;
	}
//	while (21)
//	{
//		if (env->timestamp > env->time_to_die)
//		{
//			printf("%lld %lld" DEATH "\n", env->timestamp, env->philosopher[i]);
//			while (i < env->num_of_philos)
//			{
//				pthread_detach(philo[i]);
//				i++;
//			}
//			return(0);
//		}
//	}
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
