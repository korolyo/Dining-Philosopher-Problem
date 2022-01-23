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

void	end_philos(t_env *env)
{
	unsigned int	i;
	int				var;

	i = 0;
	while (i < env->num_of_philos)
	{
		waitpid(-1, &var, 0);
		if (!var)
		{
			i = 0;
			while (i < env->num_of_philos)
				kill(env->pid[i++], SIGTERM);
			break ;
		}
		i++;
	}
}

void	*philo_alive(t_env *env)
{
	env->start_time = get_time_ms();
	env->timestamp = env->start_time;
	if (env->id % 2 == 1)
		ft_usleep(1);
	while (env->is_dead == 0)
	{
		take_forks(env);
		eat(env);
		philo_sleep(env);
		think(env);
	}
	exit(1);
}

int	threads(t_env *env)
{
	pthread_t	waiter;
	int64_t		i;

	i = 0;
	while (i < env->num_of_philos)
	{
		env->pid[i] = fork();
		if (env->pid[i] == 0)
		{
			env->id = i + 1;
			pthread_create(&waiter, NULL, &monitor, (void *) env);
			pthread_detach(waiter);
			philo_alive(env);
			exit(1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env			env;

	if (!check_argv(argc, argv))
	{
		printf("Wrong args!\n");
		return (0);
	}
	init_data(&env, argc, argv);
	threads(&env);
	end_philos(&env);
	clean_all(&env);
	return (0);
}
