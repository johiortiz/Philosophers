/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:15 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 19:12:27 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->state_mutex);
	if (philo->simu->stop)
	{
		pthread_mutex_unlock(&philo->simu->state_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->simu->state_mutex);
	return (true);
}

static bool	single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork), false);
	while (check_alive(philo))
		ft_usleep(1);
	pthread_mutex_unlock(philo->left_fork);
	return (false);
}

static bool	lock_forks(t_philo *philo, pthread_mutex_t *first,
	pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(first), false);
	pthread_mutex_lock(second);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(second),
			pthread_mutex_unlock(first), false);
	return (true);
}

static bool	take_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (single_philo(philo));
	if (philo->id % 2 == 0)
		return (lock_forks(philo, philo->right_fork, philo->left_fork));
	return (lock_forks(philo, philo->left_fork, philo->right_fork));
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (check_alive(philo))
	{
		if (!print_status(philo, "is thinking"))
			break ;
		if (!take_forks(philo))
			break ;
		if (!print_status(philo, "is sleeping"))
			break ;
		ft_usleep(philo->simu->time_to_sleep);
	}
	return (NULL);
}
