/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 21:55:15 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 22:59:46 by johyorti         ###   ########.fr       */
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