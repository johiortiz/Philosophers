/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:50:21 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/16 00:10:12 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_simu_memory(t_simu *simu)
{
	simu->forks = malloc(simu->n_philo * sizeof(pthread_mutex_t));
	if (!simu->forks)
		return (false);
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

	if (pthread_mutex_init(&simu->print_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&simu->state_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simu->print_mutex);
		return (false);
	}
	i = 0;
	while (i < simu->n_philo)
	{
		if (pthread_mutex_init(&simu->forks[i], NULL) != 0)
		{
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

bool	init_philos(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->n_philo)
	{
		simu->philos[i].id = i + 1;
		simu->philos[i].meals_eaten = 0;
		simu->philos[i].last_meal = simu->start_time;
		simu->philos[i].simu = simu;
		simu->philos[i].left_fork = &simu->forks[i];
		simu->philos[i].right_fork = &simu->forks[(i + 1) % simu->n_philo];
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
