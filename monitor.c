/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 19:03:02 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 19:34:54 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
   check_death - Verifica si algún filósofo murió
   
   Lógica:
   1. Lock state_mutex
   2. Para cada filósofo:
      if (get_time() - philos[i].last_meal > time_to_die)
         → simu->stop = true
         → return philos[i].id (el que murió)
   3. Unlock state_mutex
   
   Retorna: ID del filósofo muerto o -1 (todos vivos)
============================================================================ */
static int	check_death(t_simu *simu)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&simu->state_mutex);
	while (i < simu->n_philo)
	{
		if ((get_time() - simu->philos[i].last_meal) > simu->time_to_die)
		{
			simu->stop = true;
			pthread_mutex_unlock(&simu->state_mutex);
			return (simu->philos[i].id);
		}
		i++;
	}
	pthread_mutex_unlock(&simu->state_mutex);
	return (-1);
}   

/* ============================================================================
   check_meals - Verifica si todos comieron must_eat
   
   Si must_eat != -1:
   1. Lock state_mutex
   2. Contar cuántos philos[i].meals_eaten >= must_eat
   3. Si TODOS ≥ must_eat → simu->stop = true
   
   Retorna: true si todos terminaron comidas
============================================================================ */
static bool	check_meals(t_simu *simu)
{
	int	i;
	int	count;

	if (simu->must_eat == -1)
		return (false);
	pthread_mutex_lock(&simu->state_mutex);
	i = 0;
	count = 0;
	while (i < simu->n_philo)
	{
		if (simu->philos[i].meals_eaten >= simu->must_eat)
			count++;
		i++;
	}
	pthread_mutex_unlock(&simu->state_mutex);
	return (count == simu->n_philo);
}

/* ============================================================================
   monitor - Thread monitor principal
   
   Loop cada 1ms:
   1. check_death()
   2. check_meals()
   3. Si cualquiera true → parar
   
   ¿Por qué cada 1ms?
   - Precisión <10ms requerida [file:1]
   - ft_usleep(1000) = 1ms
   
   Retorna NULL
============================================================================ */
void	*monitor(void *data)
{
	t_simu	*simu;
	int		dead_philo;

	simu = (t_simu *)data;
	while(1)
	{
		dead_philo = check_death(simu);
		if (dead_philo != -1)
		{
			print_status(&simu->philos[dead_philo - 1], "died");
			return (NULL);
		}
		if (check_meals(simu))
			return (NULL);
		ft_usleep(1000);
	}
	return (NULL);
}