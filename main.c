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

void	*philo_alive(void *args)
{
	t_env	*env;

	env = (t_env *)args;
	printf(ANSI_COLOR_CYAN "IM I ALIVE? BUT IM HUNGRY!!\n CAN I HAVE SOME"
		" FORKS, SIR?\n" ANSI_COLOR_CYAN);
//	pthread_mutex_lock(&left_fork);
//	pthread_mutex_lock(&right_fork);
	printf("%lld %lld has taken a fork\n", env->time_to_sleep, env->count);
	usleep(env->time_to_eat);
//	pthread_mutex_unlock(&left_fork);
//	pthread_mutex_unlock(&right_fork);
	printf(ANSI_COLOR_Y "%lld %lld is sleeping\n" ANSI_COLOR_Y,
		env->time_to_sleep, env->count);
	usleep(env->time_to_sleep);
	printf(ANSI_COLOR_B "%lld %lld is thinking\n"	ANSI_COLOR_B,
		env->time_to_sleep, env->count);
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	*philo;
	int64_t		i;

	i = 0;
	philo = (pthread_t *)malloc((int)env->num_of_philos * sizeof(pthread_t));
	if (NULL == philo)
		return (0);
	while (i < env->num_of_philos)
	{
		env->count = i;
		pthread_create(&philo[i], NULL, &philo_alive, (void *) env);
		i++;
	}
	pthread_join(*philo, NULL);
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
