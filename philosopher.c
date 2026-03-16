/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:15 by johyorti          #+#    #+#             */
/*   Updated: 2026/03/16 02:29:10 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
   check_alive - Verifica si simulación sigue viva
   
   Protegido por state_mutex:
   - simu->stop = true → alguien murió
   - También chequea su propia última comida
   
   Retorna: false si debe parar
============================================================================ */
static bool	check_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->simu->state_mutex);
	if (philo->simu->stop)
	{
		pthread_mutex_unlock(&philo->simu->state_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->simu->state_mutex);
	return (true);
}

/* ============================================================================
   take_forks - Coger ambos tenedores
   
   Orden DINÁMICO anti-deadlock:
   - Impares: left → right
   - Pares: right → left
   
   Retorna: false si no puede coger ambos
============================================================================ */
static bool	take_forks(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		while (check_alive(philo))
			ft_usleep(1);
		pthread_mutex_unlock(philo->left_fork);
		return (false);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (false);
		}
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
		pthread_mutex_lock(philo->right_fork);
		if (!print_status(philo, "has taken a fork"))
		{
			pthread_mutex_unlock(philo->right_fork); 
			pthread_mutex_unlock(philo->left_fork);
			return (false);
		}
	}
	return (true);
}

/* ============================================================================
   philosopher - Rutina principal del filósofo
   
   Ciclo infinito:
   THINK → TAKE_FORKS → EAT → SLEEP → THINK → ...
   
   Para en:
   - check_alive() = false (muerte detectada)
   - take_forks() = false (no pudo comer)
   - print_status() = false
   
   Retorna NULL
============================================================================ */
void	*philosopher(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	printf("[PPHILO %d STARTED]\n", philo->id);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (check_alive(philo))
	{
		if (!print_status(philo, "is thinking"))
			break ;
		if (!take_forks(philo))
			break ;
		pthread_mutex_lock(&philo->simu->state_mutex);
		philo->last_meal = get_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->simu->state_mutex);
		if (!print_status(philo, "is eating"))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		ft_usleep(philo->simu->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (!print_status(philo, "is sleeping"))
			break ;
		ft_usleep(philo->simu->time_to_sleep);
	}
	return (NULL);
}

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
	int	i;

	if (!parse_args(ac, av, &simu))
		return (1);
	if (!init_simu(&simu))
	{
		printf("Error: Failed to initialize\n");
		return (1);
	}
	// Lanzar filósofos
	i = 0;
	while (i < simu.n_philo)
	{
		if (pthread_create(&simu.philos[i].thread, NULL, philosopher, &simu.philos[i]) != 0)
		{
			printf("Error: Failed to create philo thread\n");
			cleanup_simu(&simu);
			return (1);
		}
		i++;
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
