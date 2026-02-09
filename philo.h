/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:11 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/05 18:31:10 by johyorti         ###   ########.fr       */
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

typedef struct s_philo
{
	int		id;
	int		left_fork;
	int		right_fork;
	long	last_meal;
	t_simu	*simu;
}	t_philo;

typedef struct s_simu
{
	int					*nb_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	pthread_mutex_t		*forks;
	pthread_mutex_t		write_mutex;
	t_philo				philos;
	int					someone_died;
}	t_simu;

#endif