/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acollin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:41:28 by acollin           #+#    #+#             */
/*   Updated: 2021/11/06 19:42:12 by acollin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>

# define PHILO_MAX 200

// PHILOS STATES
# define HUNGRY		1
# define EATING		2
# define THINKING	3

//STATES OF PHILOS

# define FORK_LEFT	11
# define FORK_RIGHT	22
# define EAT			33
# define SLEEP		44
# define THINK		55
# define DEATH		66
# define ERROR		77
# define FINAL_MEAL	88

// ANSI colored output

# define FORK_LEFT_MESSAGE	"\x1b[33m has taken a fork\x1b[0m"
# define FORK_RIGHT_MESSAGE	"\x1b[33m has taken a fork\x1b[0m"
# define EAT_MESSAGE			"\x1b[35m is eating\x1b[0m"
# define SLEEP_MESSAGE		"\x1b[34m is sleeping\x1b[0m"
# define THINK_MESSAGE		"\x1b[32m is thinking\x1b[0m"
# define DEATH_MESSAGE		"\x1b[31m died\x1b[0m"
# define FINAL_MEAL_MESSAGE	"Each philosopher ate at least"
# define ERROR_MESSAGE		"\x1b[31m Error\n\x1b[0m"

typedef struct s_env	t_env;
typedef struct s_philo	t_philo;
typedef struct s_waiter	t_waiter;
typedef struct timeval	t_time;

struct		s_waiter
{
	int64_t	i;
};

struct		s_philo
{
	pid_t	pid;
	int64_t	timestamp;
	int64_t	start_time;
	int64_t	num_of_philos;
	int64_t	is_dead;
	sem_t	death;
	t_env	*env;
};

// PARSED ARGS
struct		s_env
{
	uint32_t	num_of_philos;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
	int64_t		num_of_meals;
	int64_t		counting_meals;
	pthread_t	philo[PHILO_MAX];
	sem_t		fork[PHILO_MAX];
	sem_t		message;
	t_philo		*philosopher;
};

int		check_argv(int argc, char **argv);
int		init_data(t_env *env, int argc, char **argv);
void	init_env(t_env *env, int argc, char **argv);
int		init_philo(t_env *env);
int		init_forks(t_env *env);
int64_t	get_time_ms(void);
void	write_message(t_philo *philo, int message);
char	*get_message(int message);
void	*monitor(void *args);
int		finishing(t_philo *philo, uint32_t i);
void	ft_usleep(int ms);
int		threads(t_env *env);
void	*philo_alive(t_philo *philo);
void	clean_all(t_env *env);
void	finish_semaphors(t_env *env);
void	finish_threads(t_env *env);

// ACTIONS
void	take_forks(t_philo *philo);
void	eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	think(t_philo *philo);

// SOME UTILS
int64_t	ft_atol(const char *nptr);
int		ft_isdigit(int c);

#endif
