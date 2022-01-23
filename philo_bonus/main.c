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

void	*philo_alive(t_env *env)
{
	env->start_time = get_time_ms();
	env->timestamp = env->start_time;
	if (env->id % 2 == 1)
		ft_usleep(10);
	while (!(env->is_dead))
	{
		take_forks(env);
		eat(env);
		philo_sleep(env);
		think(env);
	}
	return (NULL);
}

int	threads(t_env *env)
{
	pthread_t	waiter;
	int64_t		i;
	int			var;

	i = 0;
	while (i < env->num_of_philos)
	{
		env->pid[i] = fork();
		if (env->pid[i] == -1)
			return (0);
		if (env->pid[i] == 0)
		{
			env->id = i + 1;
			pthread_create(&waiter, NULL, &monitor, (void *) env);
			philo_alive(env);
			pthread_join(waiter, NULL);
			break ;
		}
		i++;
	}
	waitpid(-1, &var, 0);
	i = 0;
	if (var == 0)
	{
		while (i < env->num_of_philos)
			kill(env->pid[i++], SIGTERM);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;

	if (!check_argv(argc, argv))
	{
		printf("Wrong args!\n");
		return (0);
	}
	if (init_data(&env, argc, argv) == -1)
	{
		printf("Error in init\n");
		return (0);
	}
	threads(&env);
	sem_wait(env.ending);
	clean_all(&env);
	return (0);
}
