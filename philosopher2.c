/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 18:54:58 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 19:30:27 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	do_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->state_mutex);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->simu->state_mutex);
	if (!print_status(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (false);
	}
	ft_usleep(philo->simu->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

int	create_threads(t_simu *simu, pthread_t *mon)
{
	int	i;

	i = 0;
	while (i < simu->n_philo)
	{
		if (pthread_create(&simu->philos[i].thread,
				NULL, philosopher, &simu->philos[i]) != 0)
			return (printf("Error: Failed to create philo thread\n"),
				cleanup_simu(simu), 0);
		i++;
	}
	if (pthread_create(mon, NULL, monitor, &simu) != 0)
		return (printf("Error: Failed to create monitor thread\n"),
			cleanup_simu(simu), 0);
	return (0);
}

int	join_threads(t_simu *simu, pthread_t mon)
{
	int	i;

	i = 0;
	while (i < simu->n_philo)
	{
		if (pthread_join(simu->philos[i].thread, NULL))
			return (0);
		i++;
	}
	pthread_join(mon, NULL);
	return (1);
}
