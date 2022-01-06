/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:09:32 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:09:37 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argv(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (argc < 5 || ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) > PHILO_MAX)
		return (0);
	while (++j < argc)
	{
		i = 0;
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]))
				return (0);
			i++;
		}
	}
	return (1);
}

int	init_forks(t_env *env)
{
	int64_t	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		(env->philosopher + i)->right_fork = &(env->fork[i]);
		(env->philosopher + i)->left_fork = &(env->fork[(i + 1)
				% env->num_of_philos]);
		i++;
	}
	return (0);
}

int	init_philo(t_env *env)
{
	int64_t	i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos);
	if (!philo)
		return (-1);
	while (i < env->num_of_philos)
	{
		pthread_mutex_init(&philo[i].death, NULL);
		(philo + i)->is_dead = 0;
		(philo + i)->id = i + 1;
		(philo + i)->timestamp = get_time_ms();
		(philo + i)->env = env;
		i++;
	}
	env->philosopher = philo;
	return (0);
}

void	init_env(t_env *env, int argc, char **argv)
{
	env->num_of_philos = (uint32_t)ft_atol(argv[1]);
	env->time_to_die = (uint32_t)ft_atol(argv[2]);
	env->time_to_eat = (uint32_t)ft_atol(argv[3]);
	env->time_to_sleep = (uint32_t)ft_atol(argv[4]);
	env->num_of_meals = -1;
	env->counting_meals = 0;
	pthread_mutex_init(&env->message, NULL);
	if (argc > 5)
	{
		env->num_of_meals = ft_atol(argv[5]);
		env->counting_meals = env->num_of_meals * env->num_of_philos;
	}
}

int	init_data(t_env	*env, int argc, char **argv)
{
	init_env(env, argc, argv);
	if (init_philo(env) == -1)
		return (-1);
	if (init_forks(env) == -1)
		return (-1);
	return (0);
}
