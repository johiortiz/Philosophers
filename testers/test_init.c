/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 18:59:34 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 19:41:22 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
** Versión ultra simple de philosopher() para test:
** solo imprime un mensaje y termina.
*/

int	main(int ac, char **av)
{
	t_simu	simu;

	printf("=== TEST INIT ===\n\n");
	if (!parse_args(ac, av, &simu))
	{
		printf("❌ parse_args() failed\n");
		return (1);
	}
	printf("✅ parse_args() OK\n");
	printf("  n_philo      = %d\n", simu.n_philo);
	printf("  time_to_die  = %ld\n", simu.time_to_die);
	printf("  time_to_eat  = %ld\n", simu.time_to_eat);
	printf("  time_to_sleep= %ld\n", simu.time_to_sleep);
	printf("  must_eat     = %d\n\n", simu.must_eat);

	if (!init_simu(&simu))
	{
		printf("❌ init_simu() failed\n");
		return (1);
	}
	printf("✅ init_simu() OK\n");
	printf("  forks  pointer = %p\n", (void *)simu.forks);
	printf("  philos pointer = %p\n\n", (void *)simu.philos);

	printf("Sleeping 1 second to let threads run...\n\n");
	ft_usleep(1000);

	printf("Calling cleanup_simu()...\n");
	cleanup_simu(&simu);
	printf("✅ cleanup_simu() finished\n");
	printf("If you run valgrind and see 0 leaks → init/cleanup perfect\n");

	return (0);
}
