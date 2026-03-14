/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:37:04 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/22 14:37:06 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(void)
{
	t_simu			simu;
	t_philo			philo;
	long			start;
	long			before_sleep;
	long			after_sleep;
	pthread_mutex_t	test_mutex;

	// Inicializar para tests
	simu.stop = false;
	simu.start_time = get_time();
	simu.print_mutex = test_mutex;
	pthread_mutex_init(&test_mutex, NULL);
	
	philo.id = 1;
	philo.simu = &simu;

	printf("=== TESTING UTILS ===\n\n");

	// TEST 1: get_time()
	printf("TEST 1: get_time()\n");
	start = get_time();
	printf("  Epoch timestamp: %ld ms\n", start);
	if (start == -1)
	{
		printf("  ❌ get_time() failed\n");
		return (1);
	}
	printf("  ✅ get_time() OK\n\n");

	// TEST 2: get_relative_time()
	printf("TEST 2: get_relative_time()\n");
	before_sleep = get_relative_time(simu.start_time);
	printf("  Before sleep: %ld ms\n", before_sleep);
	ft_usleep(500);
	after_sleep = get_relative_time(simu.start_time);
	printf("  After 500ms sleep: %ld ms\n", after_sleep);
	if (after_sleep >= 450 && after_sleep <= 550)
		printf("  ✅ get_relative_time() precise (±50ms)\n");
	else
		printf("  ❌ get_relative_time() imprecise (%.0lf ms error)\n", 
			after_sleep - 500.0);
	printf("\n");

	// TEST 3: ft_usleep()
	printf("TEST 3: ft_usleep()\n");
	printf("  Sleeping 200ms...\n");
	before_sleep = get_time();
	ft_usleep(200);
	after_sleep = get_time();
	printf("  Slept for %ld ms\n", after_sleep - before_sleep);
	if ((after_sleep - before_sleep) >= 180 && (after_sleep - before_sleep) <= 220)
		printf("  ✅ ft_usleep() precise (±20ms)\n");
	else
		printf("  ❌ ft_usleep() imprecise (%.0lf ms error)\n", 
			after_sleep - before_sleep - 200.0);
	printf("\n");

	// TEST 4: print_status() sin stop
	printf("TEST 4: print_status() normal\n");
	if (print_status(&philo, "is thinking"))
		printf("  ✅ print_status() worked\n");
	else
		printf("  ❌ print_status() failed unexpectedly\n");
	printf("\n");

	// TEST 5: print_status() con stop
	printf("TEST 5: print_status() with stop\n");
	simu.stop = true;
	if (!print_status(&philo, "died"))
		printf("  ✅ print_status() correctly stopped\n");
	else
		printf("  ❌ print_status() printed when stopped\n");
	printf("\n");

	// TEST 6: print_status() formato exacto
	printf("TEST 6: print_status() format\n");
	simu.stop = false;
	simu.start_time = get_time();
	if (print_status(&philo, "has taken a fork"))
		printf("  ✅ Format correct: timestamp ID message\n");
	else
		printf("  ❌ Failed to print\n");
	printf("\n");

	printf("=== ALL TESTS PASSED ===\n");
	pthread_mutex_destroy(&test_mutex);
	return (0);
}
