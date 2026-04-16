/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:15 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/16 20:24:43 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_alive(t_philo *philo)
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

static bool	single_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (!print_status(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork), false);
	while (check_alive(philo))
		ft_usleep(1);
	return (pthread_mutex_unlock(philo->left_fork), false);
}

static bool	take_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
		return (single_fork(philo));
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), false);
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, "has taken a fork"))
			return (drop_forks(philo), false);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, "has taken a fork"))
			return (pthread_mutex_unlock(philo->left_fork), false);
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, "has taken a fork"))
			return (drop_forks(philo), false);
	}
	return (true);
}

void	*philosopher(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->simu->time_to_eat / 2);
	while (check_alive(philo))
	{
		if (!print_status(philo, "is thinking"))
			break ;
		if (!take_forks(philo))
			break ;
		if (!eat_philo(philo))
			break ;
		if (!sleep_and_check(philo))
			break ;
	}
	return (NULL);
}
