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

int	finishing(t_philo *philo, uint32_t i)
{
	if (get_time_ms() - philo->env->time_to_die > philo[i].timestamp
		|| (philo->env->num_of_meals >= 0 && philo->env->counting_meals < 0))
	{
		pthread_mutex_unlock(&philo[i].death);
		if (philo->env->num_of_meals >= 0
			&& philo->env->counting_meals < 0)
			write_message(&philo[i], FINAL_MEAL);
		else
			write_message(&philo[i], DEATH);
		i = 0;
		while (i < philo->env->num_of_philos)
		{
			philo[i].is_dead = 1;
			i++;
		}
		return (0);
	}
	return (1);
}

void	*monitor(void *args)
{
	t_philo		*philo;
	uint32_t	i;

	philo = (t_philo *)args;
	i = 0;
	while (21)
	{
		usleep(100);
		i = 0;
		while (i < philo->env->num_of_philos)
		{
			pthread_mutex_lock(&philo[i].death);
			if (!finishing(philo, i))
				return (NULL);
			pthread_mutex_unlock(&philo[i].death);
			i++;
		}
	}
}
