/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:03:02 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 23:08:54 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_simu *simu)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&simu->state_mutex);
	while (i < simu->n_philo)
	{
		if ((get_time() - simu->philos[i].last_meal) > simu->time_to_die)
		{
			simu->stop = true;
			pthread_mutex_unlock(&simu->state_mutex);
			return (simu->philos[i].id);
		}
		i++;
	}
	pthread_mutex_unlock(&simu->state_mutex);
	return (-1);
}

static bool	check_meals(t_simu *simu)
{
	int	i;
	int	count;

	if (simu->must_eat == -1)
		return (false);
	pthread_mutex_lock(&simu->state_mutex);
	i = 0;
	count = 0;
	while (i < simu->n_philo)
	{
		if (simu->philos[i].meals_eaten >= simu->must_eat)
			count++;
		i++;
	}
	pthread_mutex_unlock(&simu->state_mutex);
	simu->stop = (count == simu->n_philo);
	return (count == simu->n_philo);
}

void	*monitor(void *data)
{
	t_simu	*simu;
	int		dead_philo;

	simu = (t_simu *)data;
	while (1)
	{
		dead_philo = check_death(simu);
		if (dead_philo != -1)
		{
			print_status(&simu->philos[dead_philo - 1], "died");
			return (NULL);
		}
		if (check_meals(simu))
			return (NULL);
		ft_usleep(1);
	}
	return (NULL);
}
