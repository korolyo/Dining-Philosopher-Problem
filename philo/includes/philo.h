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
# define FORK_LEFT	"\x1b[33m has taken a fork left\x1b[0m"
# define FORK_RIGHT	"\x1b[33m has taken a fork right\x1b[0m"
# define EAT			"\x1b[35m is eating\x1b[0m"
# define SLEEP		"\x1b[34m is sleeping\x1b[0m"
# define THINK		"\x1b[32m is thinking\x1b[0m"
# define DEATH		"\x1b[31m died\x1b[0m"
# define ERROR		"\x1b[31m Error\x1b[0m"

typedef struct s_env	t_env;
typedef struct s_philo	t_philo;
typedef struct s_waiter	t_waiter;
typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;

struct		s_waiter
{
	int64_t	i;
};

struct		s_philo
{
	int64_t	id;
	int64_t	timestamp;
	int64_t	start_time;
	int64_t	num_of_philos;
	int64_t	is_dead;
	t_mutex	*left_fork;
	t_mutex	*right_fork;
	t_mutex	death;
	t_env	*env;
};

// PARSED ARGS
struct		s_env
{
	uint32_t	num_of_philos;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	uint64_t	num_of_meals;
	pthread_t	philo[PHILO_MAX];
	t_mutex		fork[PHILO_MAX];
	t_mutex		*message;
	t_philo		*philosopher;
};

int		check_argv(int argc, char **argv);
int		init_data(t_env *env, int argc, char **argv);
void	init_env(t_env *env, int argc, char **argv);
int		init_philo(t_env *env);
int		init_forks(t_env *env);
int64_t	get_time_ms(void);
void	ft_usleep(int ms);
int		threads(t_env *env);
void	*philo_alive(void *args);

// SOME UTILS
int64_t	ft_atol(const char *nptr);

#endif
