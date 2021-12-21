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
	if (argc < 5 || ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) > PHILO_MAX)
	{
		printf(ERROR);
		return (0);
	}
	return (1);
}

int	init_data(t_env *env, int argc, char **argv)
{
	int64_t	i;
	t_philo	*philo;

	i = 0;
	env->num_of_philos = ft_atol(argv[1]);
	env->time_to_die = ft_atol(argv[2]);
	env->time_to_eat = ft_atol(argv[3]);
	env->time_to_sleep = ft_atol(argv[4]);
	env->num_of_meals = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos);
	if (!philo)
		return (-1);
	while (i < env->num_of_philos)
	{
		(philo[i]).id = i + 1;
		philo[i].timestamp = 0;
		philo[i].state = HUNGRY;
		i++;
		printf("philo[%lld] in init = %lld\n", i, philo[i].id);
	}
	env->philosopher = philo;
	if (argc > 5)
		env->num_of_meals = ft_atol(argv[5]);
	return (env->num_of_philos);
}
