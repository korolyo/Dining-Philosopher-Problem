/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:10 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:08:22 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	finishing(t_env *env)
{
	if (get_time_ms() - env->time_to_die > env->timestamp
		|| (env->num_of_meals >= 0 && env->counting_meals <= -1))
	{
		sem_post(env->death);
		if (env->num_of_meals >= 0 && env->counting_meals <= -1)
			write_message(env, FINAL_MEAL);
		else
			write_message(env, DEATH);
		env->is_dead = 1;
		exit(0);
	}
	return (1);
}

void	*monitor(void *args)
{
	t_env		*env;
	uint32_t	i;

	env = (t_env *)args;
	i = 0;
	while (21)
	{
		usleep(100);
		i = 0;
		while (i < env->num_of_philos)
		{
			sem_wait(env->death);
			if (!finishing(env))
				return (NULL);
			sem_post(env->death);
			i++;
		}
	}
}
