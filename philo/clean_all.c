/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:57 by acollin           #+#    #+#             */
/*   Updated: 2021/12/05 16:09:22 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_mutexes(t_env *env)
{
	int64_t	i;

	i = 0;
	pthread_mutex_destroy(env->fork);
	while (i < env->num_of_philos)
	{
		pthread_mutex_unlock(&(env->fork[i]));
		pthread_mutex_unlock(&(env->philosopher[i].death));
		pthread_mutex_destroy(&(env->fork[i]));
		pthread_mutex_destroy(&(env->philosopher[i].death));
		i++;
	}
	pthread_mutex_destroy(&(env->message));
}

void	finish_threads(t_env *env)
{
	int64_t	i;

	i = 0;
	while (i < env->num_of_philos)
	{
		pthread_detach(env->philo[i]);
		i++;
	}
	free(env->philosopher);
}

void	clean_all(t_env *env)
{
	finish_threads(env);
	finish_mutexes(env);
}
