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

#include "philo.h"

void	*monitor(void *args)
{
	t_philo		*philo;
	uint32_t	i;
	int64_t		time_ms;

	philo = (t_philo *)args;
	i = 0;
	while (21)
	{
		usleep(100);
		i = 0;
		while (i < philo->env->num_of_philos)
		{
			time_ms = get_time_ms();
			pthread_mutex_lock(&philo[i].death);
			if (time_ms - philo->env->time_to_die > philo[i].timestamp)
			{
				pthread_mutex_unlock(&philo[i].death);
				write_message(&philo[i], DEATH);
				i = 0;
				while (i < philo->env->num_of_philos)
				{
					philo[i].is_dead = 1;
					i++;
				}
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].death);
			i++;
		}
	}
}
