/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:23:39 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 19:41:50 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simu	simu;
	pthread_t	monitor_thread;

	if (!parse_args(ac, av, &simu))
		return (1);
	if (!init_simu(&simu))
	{
		printf("Error: Failed to initialize\n");
		return (1);
	}
	// Crear monitor thread
	if (pthread_create(&monitor_thread, NULL, monitor, &simu) != 0)
	{
		cleanup_simu(&simu);
		return (1);
	}
	// Esperar a monitor
	pthread_join(monitor_thread, NULL);
	// Cleanup
	cleanup_simu(&simu);
	return (0);
}
