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
# include <unistd.h>

# define PHILO_MAX 200

//From EXAMPLE. mb DELETE after...==========
# define ERROR_CREATE_THREAD -11
# define ERROR_JOIN_THREAD -12
# define SUCCESS 0
# define BAD_MESSAGE -1
//===========================================

// ANSI colored output
# define ANSI_COLOR_R		"\x1b[31m"
# define ANSI_COLOR_G		"\x1b[32m"
# define ANSI_COLOR_Y		"\x1b[33m"
# define ANSI_COLOR_B		"\x1b[34m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

// GLOBAL FOR MUTEX
pthread_mutex_t left_fork;
pthread_mutex_t right_fork;

typedef struct s_env	t_env;
typedef struct s_philo	t_philo;

// PARSED ARGS
struct	s_env
{
	int64_t	num_of_philos;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int64_t	num_of_meals;
	int64_t	count;
};

// PHILOSOPHERs
struct	s_philo
{
	int	left_hand;
	int	right_hand;
};

void	check_argv(int argc, char **argv);
int64_t	init_data(t_env *env, int argc, char **argv);
int		threads(t_env *env);
void	*philo_alive(void *args);

// SOME UTILS
int64_t	ft_atol(const char *nptr);

#endif
