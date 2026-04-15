/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:22:55 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 18:20:02 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	ft_atol(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

static void	print_usage(char *program_name)
{
	printf("Error: Invalid arguments\n\n");
	printf("Usage: %s number_of_philosophers time_to_die time_to_eat ",
		program_name);
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	printf("Arguments:\n");
	printf("  number_of_philosophers: Number of philosophers (1-200)\n");
	printf("  time_to_die:            Time in ms before dying (> 0)\n");
	printf("  time_to_eat:            Time in ms to eat (> 0)\n");
	printf("  time_to_sleep:          Time in ms to sleep (> 0)\n");
	printf("  [must_eat]:             Optional: times each must eat (> 0)\n");
}

static bool	validate_args(t_simu *simu)
{
	if (simu->n_philo < 1)
		return (printf("Error: number_of_philosophers must be at leat 1\n"),
			false);
	if (simu->n_philo > 200)
		return (printf("Error: Too many philosophers (max 200)\n"), false);
	if (simu->time_to_die <= 0)
		return (printf("Error: time_to_die must be positive\n"), false);
	if (simu->time_to_eat <= 0)
		return (printf("Error: time_to_eat must be positive\n"), false);
	if (simu->time_to_sleep <= 0)
		return (printf("Error: time_to_sleep must be positive\n"), false);
	if (simu->must_eat == 0)
		return (printf("Error: must_eat must be a valid positive number\n"),
			false);
	return (true);
}

bool	parse_args(int ac, char **av, t_simu *simu)
{
	if (ac < 5 || ac > 6)
		return (print_usage(av[0]), false);
	simu->n_philo = (int)ft_atol(av[1]);
	simu->time_to_die = ft_atol(av[2]);
	simu->time_to_eat = ft_atol(av[3]);
	simu->time_to_sleep = ft_atol(av[4]);
	if (simu->n_philo == -1 || simu->time_to_die == -1 || simu->time_to_eat
		== -1 || simu->time_to_sleep == -1)
		return (printf("Error: Arguments must be valid positive numbers\n"),
			false);
	if (ac == 6)
	{
		simu->must_eat = (int)ft_atol(av[5]);
		if (simu->must_eat == -1)
			return (printf("Error: must_eat must be a valid positive number\n"),
				false);
	}
	else
		simu->must_eat = -1;
	if (!validate_args(simu))
		return (false);
	return (simu->stop = false, simu->start_time = 0,
		simu->forks = NULL, simu->philos = NULL, true);
}
