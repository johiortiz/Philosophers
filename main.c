/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:23:39 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 19:50:48 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
   main - Flujo principal del programa
   
   Secuencia:
   1. parse_args() → leer argumentos
   2. init_simu() → malloc + mutexes + threads filósofos
   3. pthread_create(monitor) → thread de detección
   4. pthread_join(monitor) → esperar fin simulación
   5. cleanup_simu() → join filósofos + free todo
   
   Retorna: 0 si todo OK
============================================================================ */
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
		printf("Error: Failed to create monitor thread\n");
		cleanup_simu(&simu);
		return (1);
	}
	// Esperar a monitor
	pthread_join(monitor_thread, NULL);
	// Cleanup
	cleanup_simu(&simu);
	return (0);
}
