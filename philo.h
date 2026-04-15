/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:11 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 19:12:21 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

/* ------------------------- STRUCTS -------------------------------*/

typedef struct s_philo	t_philo;

typedef struct s_simu
{
	int					n_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	int					must_eat;
	bool				stop;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		state_mutex;
	t_philo				*philos;
}	t_simu;

typedef struct s_philo
{
	int						id;
	int						meals_eaten;
	long					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_simu					*simu;
}	t_philo;

/* ----------------------------- FUNCTIONS ---------------------------*/

bool	parse_args(int ac, char **av, t_simu *simu);
long	get_time(void);
long	get_relative_time(long start_time);
void	ft_usleep(long ms);
bool	print_status(t_philo *philo, char *status);
bool	init_simu(t_simu *simu);
void	cleanup_simu(t_simu *simu);
void	*philosopher(void *data);
bool	init_philos(t_simu *simu);
void	*monitor(void *data);
bool	do_eat(t_philo *philo);
int		create_threads(t_simu *simu, pthread_t *mon);
int		join_threads(t_simu *simu, pthread_t mon);


#endif