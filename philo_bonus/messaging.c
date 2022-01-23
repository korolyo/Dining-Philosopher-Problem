/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messaging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:10 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:08:22 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*get_message(int message)
{
	if (message == FORK_RIGHT)
		return (FORK_RIGHT_MESSAGE);
	if (message == FORK_LEFT)
		return (FORK_LEFT_MESSAGE);
	if (message == EAT)
		return (EAT_MESSAGE);
	if (message == SLEEP)
		return (SLEEP_MESSAGE);
	if (message == THINK)
		return (THINK_MESSAGE);
	if (message == DEATH)
		return (DEATH_MESSAGE);
	return (ERROR_MESSAGE);
}

void	write_message(t_env *env, int message)
{
	sem_wait(env->message);
	if (message != FINAL_MEAL)
		printf("%lld %lld%s\n", get_time_ms() - env->start_time, env->id,
			get_message(message));
	if (message == DEATH || message == FINAL_MEAL)
	{
		if (message == FINAL_MEAL)
			printf(FINAL_MEAL_MESSAGE " %lld times\n", env->num_of_meals);
		return ;
	}
	sem_post(env->message);
}
