/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:11 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 19:16:06 by johyorti         ###   ########.fr       */
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

/* ============================================================================
   FORWARD DECLARATION
   
   ¿Por qué necesitamos esto?
   - t_simu contiene puntero a t_philo (línea 38)
   - t_philo contiene puntero a t_simu (línea 53)
   - Dependencia circular → necesitamos declarar uno antes
   
   Solución:
   1. Declarar t_philo primero (typedef struct s_philo t_philo)
   2. Definir t_simu (que usa t_philo*)
   3. Definir struct s_philo completa
   ============================================================================ */

typedef struct s_philo	t_philo;

// ESTRUCTURA PRINCIPAL: t_simu
// Contiene configuración global de la simulación
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

// ESTRUCTURA: t_philo (definición completa)
// Datos individuales de cada filósofo

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

/* ---------------------------------- FUNCTIONS ---------------------------------*/

// Parsing
bool	parse_args(int ac, char **av, t_simu *simu);

// Utils
long	get_time(void);
long	get_relative_time(long start_time);
void	ft_usleep(long ms);
bool	print_status(t_philo *philo, char *status);

// Init
bool	init_simu(t_simu *simu);
void	cleanup_simu(t_simu *simu);
void	*philosopher(void *data);

// Monitor
void	*monitor(void *data);



#endif