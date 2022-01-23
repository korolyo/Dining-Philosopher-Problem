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

void	*monitor(void *args)
{
	t_env		*env;
	uint32_t	i;

	env = (t_env *)args;
	i = 0;
	while (21)
	{
		usleep(1000);
		if (get_time_ms() - env->time_to_die > env->timestamp
			|| (env->num_of_meals >= 0 && env->counting_meals <= -1))
		{
			sem_post(env->death);
			if (env->num_of_meals >= 0 && env->counting_meals <= -1)
				write_message(env, FINAL_MEAL);
			else
				write_message(env, DEATH);
			env->is_dead = 1;
			exit (0);
		}
	}
}
