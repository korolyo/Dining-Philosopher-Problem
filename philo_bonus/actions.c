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

void	take_forks(t_philo *philo)
{
	sem_wait(philo->env->forks);
	sem_wait(philo->env->forks);
	printf("test\n");
	write_message(philo, FORK_LEFT);
	write_message(philo, FORK_RIGHT);
}

void	eat(t_philo *philo)
{
	philo->timestamp = get_time_ms();
	write_message(philo, EAT);
	ft_usleep(philo->env->time_to_eat);
	philo->env->counting_meals--;
	sem_post(philo->env->forks);
	sem_post(philo->env->forks);
}

void	philo_sleep(t_philo *philo)
{
	write_message(philo, SLEEP);
	ft_usleep(philo->env->time_to_sleep);
}

void	think(t_philo *philo)
{
	write_message(philo, THINK);
}
