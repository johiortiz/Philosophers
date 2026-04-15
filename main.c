/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 19:09:59 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 19:10:15 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simu		simu;
	pthread_t	mon;

	if (!parse_args(ac, av, &simu))
		return (1);
	if (!init_simu(&simu))
		return (printf("Error: Failed to initialize\n"), 1);
	if (!create_threads(&simu, &mon))
		return (1);
	join_threads(&simu, mon);
	return (cleanup_simu(&simu), 0);
}
