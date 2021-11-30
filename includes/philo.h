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

//From EXAMPLE. mb DELETE after...==========
# define ERROR_CREATE_THREAD -11
# define ERROR_JOIN_THREAD -12
# define SUCCESS 0
# define BAD_MESSAGE "I'm dead"
//===========================================

// colored output
# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_GREEN	"\x1b[32m"
# define ANSI_COLOR_YELLOW	"\x1b[33m"
# define ANSI_COLOR_BLUE		"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

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

void	init_data(t_philo *philo);
void	check_argv(t_philo *philo, int argc, char **argv);
int64_t	ft_atol(const char *nptr);

#endif
