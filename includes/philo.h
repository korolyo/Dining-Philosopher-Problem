/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/11/06 19:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo	t_philo;

struct	s_philo
{
	int		left_hand;
	int		right_hand;
	int64_t	number_of_philosophers;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
};

void	init_data(t_philo *philos);
void	check_argv(t_philo *philos, int argc, char **argv);
int64_t	ft_atol(const char *nptr);

#endif
