/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:11 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/12 19:49:13 by johyorti         ###   ########.fr       */
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

/* ---------------------------------- STRUCTS ---------------------------------*/

typedef struct s_simu
{
	int					n_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	int					must_eat;		// por ejemplo -1 no existe
	bool				stop;			// flag: alguien murió o todos comieron
	pthread_mutex_t		*forks;			// array de N mutex (uno por tenedor)
	pthread_mutex_t		print_mutex;	// proteger printf/write
	pthread_mutex_t		state_mutex;	// para stop + datos compartidos
	t_philo				*philos;		// proteger stop, meals, etc.
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


#endif