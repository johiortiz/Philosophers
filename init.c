/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:50:21 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/22 15:43:34 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_simu_memory(t_simu *simu)
{
	// 1. Array de mutexes = n_philo forks = n_philo mutex
	simu->forks = malloc(simu->n_philo * sizeof(pthread_mutex_t));
	if (!simu->forks)
		return (false);
	// 2. Array de filósofos: n_philo filósofos
	simu->philos = malloc(simu->n_philo * sizeof(t_philo));
	if (!simu->philos)
	{
		free(simu->forks);
		return (false);
	}
	return (true);
}

static bool	init_mutexes(t_simu *simu)
{
	int	i;

	// 1. Mutex para printf (evitar mensajes mezclados [file:1])
	if (pthread_mutex_init(&simu->print_mutex, NULL) != 0)
		return (false);
	// 2. Mutex para datos compartidos (stop, last_meal)
	if (pthread_mutex_init(&simu->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simu->print_mutex);
		return (false);
	}
	// 3. Array de forks (n_philo mutexes)
	i  = 0;
	while (i < simu->n_philo)
	{
		if (pthread_mutex_init(&simu->forks[i], NULL) != 0)
		{
			// Limpiar TODOS los mutexes creados
			while (--i >= 0)
				pthread_mutex_destroy(&simu->forks[i]);
			pthread_mutex_destroy(&simu->print_mutex);
			pthread_mutex_destroy(&simu->state_mutex);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_philos(t_simu *simu)
{
	int	i;
	
	i = 0;
	while (i < simu->n_philo)
	{
		// CONFIGURAR filósofo i
		simu->philos[i].id = i + 1;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].last_meal = simu->start_time,
		simu->philos[i].simu = simu;
		
		// FORKS CIRCULARES (mesa redonda [file:1])
		simu->philos[i].left_fork = &simu->forks[i];
		simu->philos[i].right_fork = &simu->forks[(i + 1) % simu->n_philo];
		
		// CREAR THREAD
		if(pthread_create(&simu->philos[i].thread, NULL, philosopher, &simu->philos[i]) != 0)
		{
			// FALLBACK: detach threads creados
			while (--i >= 0)
				pthread_detach(simu->philos[i].thread);
			return (false);
		}
		i++;
	}
	return (true);
}

void	cleanup_simu(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->n_philo)
	{
		pthread_join(simu->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < simu->n_philo)
	{
		pthread_mutex_destroy(&simu->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&simu->print_mutex);
	pthread_mutex_destroy(&simu->state_mutex);
	free(simu->forks);
	free(simu->philos);
}

bool	init_simu(t_simu *simu)
{
	if (!init_simu_memory(simu))
		return (false);
	if (!init_mutexes(simu))
	{
		free(simu->forks);
		free(simu->philos);
		return (false);
	}
	simu->start_time = get_time();
	if (!init_philos(simu))
	{
		cleanup_simu(simu);
		return (false);
	}
	return (true);
}