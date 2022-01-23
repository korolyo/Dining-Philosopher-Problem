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

#include "philo_bonus.h"

void	finish_semaphores(t_env *env)
{
	sem_unlink(FORKS_SEM);
	sem_unlink(MESSAGE_SEM);
	sem_unlink(DEATH_SEM);
	sem_close(env->forks);
	sem_close(env->death);
	sem_close(env->message);
}

void	clean_all(t_env *env)
{
	free(env->pid);
	finish_semaphores(env);
}
