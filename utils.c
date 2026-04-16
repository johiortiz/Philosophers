/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:23:43 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/16 09:20:03 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long	get_relative_time(long start_time)
{
	return (get_time() - start_time);
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

bool	print_status(t_philo *philo, char *status)
{
	bool	is_death;
	bool	stopped;

	is_death = (strcmp(status, "died") == 0);
	pthread_mutex_lock(&philo->simu->state_mutex);
	stopped = philo->simu->stop;
	pthread_mutex_unlock(&philo->simu->state_mutex);
	if (stopped && !is_death)
		return (false);
	pthread_mutex_lock(&philo->simu->print_mutex);
	printf("%ld %d %s\n", get_relative_time(philo->simu->start_time),
		philo->id, status);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	return (true);
}
