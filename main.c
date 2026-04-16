/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:21:35 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/16 18:33:25 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	join_philos(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->n_philo)
	{
		if (pthread_join(simu->philos[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

static int	create_thread(t_simu *simu)
{
	int	i;

	simu->start_time = get_time();
	i = 0;
	while (i < simu->n_philo)
	{
		if (pthread_create(&simu->philos[i].thread, NULL,
				philosopher, &simu->philos[i]) != 0)
		{
			printf("Error: Failed to create philo thread\n");
			cleanup_forks(simu, simu->n_philo);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_simu			simu;
	pthread_t		monitor_thread;

	if (!parse_args(ac, av, &simu))
		return (1);
	if (!init_simu(&simu))
	{
		printf("Error: Failed to initialize\n");
		return (1);
	}
	if (!create_thread(&simu))
		return (1);
	if (pthread_create(&monitor_thread, NULL, monitor, &simu) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		cleanup_forks(&simu, simu.n_philo);
		return (1);
	}
	if (!join_philos(&simu))
		return (1);
	pthread_join(monitor_thread, NULL);
	cleanup_forks(&simu, simu.n_philo);
	return (0);
}
