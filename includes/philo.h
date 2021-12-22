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

// PHILOS STATES
# define HUNGRY		1
# define EATING		2
# define THINKING	3

//From EXAMPLE. mb DELETE after...==========
# define ERROR_CREATE_THREAD -11
# define ERROR_JOIN_THREAD -12
# define SUCCESS 0
# define BAD_MESSAGE -1
//===========================================

// ANSI colored output
# define FORK		"\x1b[33m has taken a fork\x1b[33m"
# define EAT			"\x1b[35m is eating\x1b[35m"
# define SLEEP		"\x1b[34m is sleeping\x1b[34m"
# define THINK		"\x1b[32m is thinking\x1b[32m"
# define DEATH		"\x1b[31m died\x1b[31m"
# define ERROR		"\x1b[31m Error\x1b[31m"

typedef struct s_env	t_env;
typedef struct s_philo	t_philo;
typedef pthread_mutex_t	mutex;
typedef	struct	timeval	t_time;

struct		s_philo
{
	int64_t	id;
	int64_t timestamp;
	int64_t state;
	int64_t	num_of_philos;
	mutex 	*left_fork;
	mutex 	*right_fork;
	t_env	*env;
};

// PARSED ARGS
struct		s_env
{
	int64_t	num_of_philos;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int64_t	num_of_meals;
	mutex 	fork[PHILO_MAX];
	t_philo *philosopher;
};

int		check_argv(int argc, char **argv);
int		init_data(t_env *env, int argc, char **argv);
int		init_philo(t_env *env);
int		threads(t_env *env);
void	*philo_alive(void *args);
int		gettime_ms();

// SOME UTILS
int64_t	ft_atol(const char *nptr);

#endif
