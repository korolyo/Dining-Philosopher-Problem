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

#include "philo_bonus.h"

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

void	init_env(t_env *env, int argc, char **argv)
{
	env->num_of_philos = (unsigned int)ft_atol(argv[1]);
	env->time_to_die = (unsigned int)ft_atol(argv[2]);
	env->time_to_eat = (unsigned int)ft_atol(argv[3]);
	env->time_to_sleep = (unsigned int)ft_atol(argv[4]);
	env->num_of_meals = -1;
	env->counting_meals = 0;
	env->id = 0;
	env->timestamp = get_time_ms();
	env->is_dead = 0;
	env->pid = (pid_t *)malloc(sizeof(pid_t) * env->num_of_philos);
	sem_unlink(FORKS_SEM);
	sem_unlink(MESSAGE_SEM);
	sem_unlink(DEATH_SEM);
	env->forks = sem_open(FORKS_SEM, O_CREAT, S_IRWXU | S_IRWXG,
			env->num_of_philos);
	env->message = sem_open(MESSAGE_SEM, O_CREAT, S_IRWXU | S_IRWXG, 1);
	env->death = sem_open(DEATH_SEM, O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (argc > 5)
	{
		env->num_of_meals = ft_atol(argv[5]);
		env->counting_meals = env->num_of_meals;
	}
}

int	init_data(t_env	*env, int argc, char **argv)
{
	init_env(env, argc, argv);
	return (0);
}
