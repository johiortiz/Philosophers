/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:39:03 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/16 20:34:01 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->simu->state_mutex);
	(*philo)->last_meal = get_time();
	(*philo)->meals_eaten++;
	pthread_mutex_unlock(&(*philo)->simu->state_mutex);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

bool	eat_philo(t_philo *philo)
{
	update_meals(&philo);
	if (!print_status(philo, "is eating"))
	{
		drop_forks(philo);
		return (false);
	}
	ft_usleep(philo->simu->time_to_eat);
	drop_forks(philo);
	return (true);
}

bool	sleep_and_check(t_philo *philo)
{
	if (!print_status(philo, "is sleeping"))
		return (false);
	ft_usleep(philo->simu->time_to_sleep);
	if (philo->simu->must_eat != -1)
	{
		if (philo->meals_eaten >= philo->simu->must_eat)
			return (false);
	}
	return (true);
}
