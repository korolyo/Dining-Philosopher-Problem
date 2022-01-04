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

void	write_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->env->message);
	printf("%lld %lld%s\n", get_time_ms() - philo->start_time,
		philo->id, message);
	pthread_mutex_unlock(philo->env->message);
}

void	*monitor(void *args)
{
	t_env		*env;
	uint32_t	i;
	int64_t		time_ms;

	env = (t_env *)args;
	i = 0;
	while (21)
	{
		usleep(100);
		i = 0;
		while (i < env->num_of_philos)
		{
			time_ms = get_time_ms();
			if (time_ms - env->time_to_die > env->philosopher[i].timestamp)
			{
				env->philosopher[i].is_dead = 1;
				write_message(&env->philosopher[i], DEATH);
				return (NULL);
			}
			i++;
		}
	}
}

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
		write_message(philo, THINK);
		pthread_mutex_lock(philo->left_fork);
		write_message(philo, FORK_LEFT);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->death);
		philo->timestamp = get_time_ms();
		write_message(philo, FORK_RIGHT);
		write_message(philo, EAT);
		ft_usleep(philo->env->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->death);
		write_message(philo, SLEEP);
		ft_usleep(philo->env->time_to_sleep);
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
		sem_init(&(env->fork[i]), 0, 0);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		fork();
		pthread_create(&(env->philo)[i], NULL, &philo_alive,
			(void *)(env->philosopher + i));
		i++;
	}
	pthread_create(&waiter, NULL, &monitor, (void *)env);
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
		printf(ERROR);
		return (0);
	}
	threads(&env);
	return (0);
}
