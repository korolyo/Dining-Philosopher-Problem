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
	while (21)
	{
		pthread_mutex_lock(&((env->fork)[env->count]));
		pthread_mutex_lock(&((env->fork)[env->count + 1]));
		printf(ANSI_COLOR_CYAN "%lld %lld has taken a fork\n" ANSI_COLOR_CYAN,
			env->time_to_sleep, env->count);
		printf(ANSI_COLOR_CYAN "%lld %lld has taken a fork\n" ANSI_COLOR_CYAN,
			env->time_to_sleep, env->count);
		printf(ANSI_COLOR_G "%lld %lld is eating\n" ANSI_COLOR_G,
			env->time_to_sleep, env->count);
		usleep(env->time_to_eat);
		printf(ANSI_COLOR_Y "%lld %lld is sleeping\n" ANSI_COLOR_Y,
			env->time_to_sleep, env->count);
		usleep(env->time_to_sleep);
		pthread_mutex_unlock(&((env->fork)[env->count]));
		pthread_mutex_unlock(&((env->fork)[env->count + 1]));
		printf(ANSI_COLOR_B
		"%lld %lld is thinking\n"
		ANSI_COLOR_B,
				env->time_to_sleep, env->count);
		while (env->count < env->num_of_philos)
			env->count++;
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t		philo[PHILO_MAX];
//	mutex			fork[PHILO_MAX];
	int64_t			i;

	i = 0;
//	env->fork = fork;
	while (i < env->num_of_philos - 1)
	{
		printf("check\n");
		pthread_mutex_init(&(env->fork[i]), NULL);
		i++;
	}
	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_create(&philo[i], NULL, &philo_alive, (void *) env);
//		usleep(4000);
		i = env->count;
	}
//	printf("check - out\n");
//	while (21)
//	{
//		if (time < env->time_to_die)
//			printf(ANSI_COLOR_R "%lld %lld died\n" ANSI_COLOR_R,
//				env->time_to_sleep, env->count);
//	}
	i = 0;
	while (i < env->num_of_philos)
	{
		printf("check - join\n");
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
