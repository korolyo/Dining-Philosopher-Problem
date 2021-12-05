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

void	check_argv(int argc, char **argv)
{
	if (argc < 5 || ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) > INT_MAX)
		printf(ANSI_COLOR_R "Error" ANSI_COLOR_R"\n");
}

int64_t	init_data(t_env *env, int argc, char **argv)
{
	env->num_of_philos = ft_atol(argv[1]);
	env->time_to_die = ft_atol(argv[2]);
	env->time_to_eat = ft_atol(argv[3]);
	env->time_to_sleep = ft_atol(argv[4]);
	env->num_of_meals = 0;
	if (argc > 5)
		env->num_of_meals = ft_atol(argv[5]);
	return (env->num_of_philos);
}
