/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:15 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/16 19:11:59 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_simu	simu;
	
	if (!parse_args(ac, av, &simu))
		return (error);
	if (!init_simu(&simu))
		return (error);
	if (!init_mutexes(&simu))
		return (error);
	if (!init_philos(&simu))
		return (error);
}