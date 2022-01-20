/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:10 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:08:22 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_env *env)
{
	sem_wait(env->forks);
	sem_wait(env->forks);
	write_message(env, FORK_LEFT);
	write_message(env, FORK_RIGHT);
}

void	eat(t_env *env)
{
	env->timestamp = get_time_ms();
	write_message(env, EAT);
	ft_usleep(env->time_to_eat);
	env->counting_meals--;
	sem_post(env->forks);
	sem_post(env->forks);
}

void	philo_sleep(t_env *env)
{
	write_message(env, SLEEP);
	ft_usleep(env->time_to_sleep);
}

void	think(t_env *env)
{
	write_message(env, THINK);
}
