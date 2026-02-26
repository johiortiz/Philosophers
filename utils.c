/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:23:43 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/26 18:34:18 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
get_time()
→ consigo “qué hora es” en ms (desde 1970) usando gettimeofday.

get_relative_time(start)
→ convierto esa hora enorme en “cuánto tiempo ha pasado desde que empezó la simulación”.

ft_usleep(ms)
→ duermo aprox ms ms, pero corrigiendo con un bucle para no pasarme demasiado.

print_status(philo, "is eating")
→ imprimo timestamp id mensaje de forma segura, sin mezclar mensajes y respetando stop.
*/

/* ============================================================================
   get_time - Obtiene timestamp actual en milisegundos
   
   ¿Por qué necesitamos esto?
   - Los logs requieren timestamp en ms [file:1]
   - Necesitamos calcular: tiempo_actual - start_time
   - Base: Unix epoch (1 enero 1970)
   
   gettimeofday() retorna:
   - tv_sec: segundos desde epoch
   - tv_usec: microsegundos adicionales (0-999999)
   
   Conversión a milisegundos:
   - ms = (segundos * 1000) + (microsegundos / 1000)
============================================================================ */
long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* ============================================================================
   get_relative_time - Tiempo relativo desde start_time
   
   Uso: timestamp = get_relative_time(simu->start_time)
   
   ¿Por qué?
   - Los logs deben ser desde inicio de simulación, no epoch
   - Formato requerido: timestamp_in_ms desde start_time [file:1]
   
   Retorna: ms transcurridos desde start_time
============================================================================ */
long	get_relative_time(long start_time)
{
	return (get_time() - start_time);
}

/* ============================================================================
   ft_usleep - Sleep preciso en milisegundos
   
   ¿Por qué mejor que usleep()?
   - usleep() tiene precisión limitada (±10ms)
   - Necesitamos timing exacto para time_to_die < 10ms [file:1]
   
   Algoritmo:
   1. Sleep inicial con usleep(100us)
   2. Loop fino: check si ya pasó el tiempo exacto
   
   Retorna: nada, pero timing preciso
============================================================================ */
void	ft_usleep(long ms)
{
	long	start;
	
	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

/* ============================================================================
   print_status - Imprime estado thread-safe
   
   Formato exacto requerido [file:1]:
   timestamp_in_ms X has taken a fork
   timestamp_in_ms X is eating
   timestamp_in_ms X is sleeping  
   timestamp_in_ms X is thinking
   timestamp_in_ms X died
   
   ¿Por qué print_mutex?
   - Evita mensajes mezclados/incompletos [file:1]
   - Múltiples threads escribiendo printf simultáneamente
   
   ¿Por qué check simu->stop?
   - No imprimir después de que alguien muera
   
   Retorna: false si simulación ya terminó
============================================================================ */
bool	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->simu->print_mutex);
	if (philo->simu->stop)
	{
		pthread_mutex_unlock(&philo->simu->print_mutex);
		return (false);
	}
	printf("%ld %d %s\n", get_relative_time(philo->simu->start_time),
		philo->id, status);
	pthread_mutex_unlock(&philo->simu->print_mutex);
	return (true);
}   