/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:22:55 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/17 12:05:20 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ============================================================================
   ft_atol - Convierte string a long con validación
   
   ¿Por qué no usar atoi()?
   - atoi() retorna 0 para inputs inválidos ("abc" → 0)
   - atoi() no detecta overflow
   - atoi() acepta negativos (no queremos eso)
   
   Retorna:
   - Número positivo si válido
   - -1 si hay error (negativo, no numérico, overflow)
============================================================================ */

static long	ft_atol(const char *str)
{
	long	result;
	int		i;
	
	result = 0;
	i = 0;

	// Saltar espacios (aunque no deberían exitir en av[])
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	// ¿Por qué rechazar signos?
	// - Los valores deben ser positivos (tiempo, cantidad)
	// - Simplifica validación
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (-1);	// Rechazar negativos
	// ¿Por qué validar cada carácter?
	// - Detectar inputs como "123abc" que atoi() convertiría mal
	// - Asegurar que TODO el string es numérico
	if (!str[i])  // String vacío o solo "+"
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		// ¿Por qué verificar overflow?
		// - INT_MAX = 2,147,483,647
		// - Prevenir comportamiento indefinido
		// - Si result * 10 + dígito > INT_MAX → overflow
		if (result > (INT_MAX - (str[i] - '0')) / 10)
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}


/* ============================================================================
   print_usage - Muestra ayuda al usuario
   
   ¿Por qué una función separada?
   - Reutilizable (DRY principle)
   - Centraliza el mensaje de error
   - Fácil de mantener/actualizar
============================================================================ */

static void	print_usage(char *program_name)
{
	printf("Error: Invalid arguments\n\n");
	printf("Usage: %s number_of_philosophers time_to_die time_to_eat ", program_name);
	printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	printf("Arguments:\n");
	printf("  number_of_philosophers: Number of philosophers (1-200)\n");
	printf("  time_to_die:            Time in ms before dying (> 0)\n");
	printf("  time_to_eat:            Time in ms to eat (> 0)\n");
	printf("  time_to_sleep:          Time in ms to sleep (> 0)\n");
	printf("  [must_eat]:             Optional: times each must eat (> 0)\n");
}

/* ============================================================================
   validate_args - Valida rangos de valores
   
   ¿Por qué separar validación de parsing?
   - Separación de responsabilidades
   - Más fácil de testear
   - Permite cambiar rangos sin tocar parsing
   
   Reglas de validación:
   - n_philo: 1-200 (200 es arbitrario pero razonable)
   - Tiempos: deben ser > 0 (0 no tiene sentido lógico)
   - must_eat: -1 (no especificado) o > 0
============================================================================ */

static bool	validate_args(t_simu *simu)
{
	// ¿Por qué vañidar n_philo >= 1?
	// - 0 filósofos no tiene sentido
	// - Caso especial: 1 filósofo (debe morir porque solo hay 1 tenedor)
	if (simu->n_philo < 1)
	{
		printf("Error: number_of_philosophers must be at leat 1\n");
		return (false);
	}
	// ¿Por qué límite de 200?
	// - Más threads = más overhead del sistema
	// - TODO: Ajustar para hacer testeo, el subject no pone límite.
	if (simu->n_philo > 200)
	{
		printf("Error: Too many philosophers (max 200)\n");
		return (false);
	}
	// ¿Por qué time_to_die debe ser > 0?
	// - 0 significa muerte instantánea -> imposible comer
	// - Aunque sea válido lógico, no tiene sentido testear
	if (simu->time_to_die <= 0)
	{
		printf("Error: time_to_die must be positive\n");
		return (false);
	}
	// ¿Por qué time_to_eat/sleep pueden ser 0?
	// - Técnicamente válido (comer/dormir instantáneo)
	// - Pero vamos a requerir > 0 para evitar edge cases raros
	if (simu->time_to_eat <= 0)
	{
		printf("Error: time_to_eat must be positive\n");
		return (false);
	}
	if (simu->time_to_sleep <= 0)
	{
		printf("Error: time_to_sleep must be positive\n");
		return (false);
	}
	// must_eat puede ser -1 (no especificado) o > 0
	if (simu->must_eat == 0)
	{
		printf("Error: number_of_times_each_philosopher_must_eat must be positive\n");
		return (false);
	}
	return (true);
}

/* ============================================================================
   parse_args - Función principal de parsing
   
   ¿Qué hace?
   1. Valida número de argumentos
   2. Convierte strings a números con ft_atol()
   3. Valida rangos con validate_args()
   4. Inicializa campos de t_simu
   
   Retorna:
   - true si todo OK
   - false si hay error (con mensaje al usuario)
============================================================================ */

bool	parse_args(int ac, char **av, t_simu *simu)
{
	// ¿Por qué validar ac primero?
	// - Evitar acceder a av[índice] fuera de bounds
	// - ac incluye el nombre del programa (av[0])
	// - ac = 5: 4 args obligatorios
	// - ac = 6: 4 obligatorios + 1 opcional
	if (ac < 5 || ac > 6)
	{
		print_usage(av[0]);
		return (false);
	}
	
	/*
	// ===== DEBUG: Ver qué recibimos =====
	printf("DEBUG: av[1] = '%s'\n", av[1]);
	printf("DEBUG: av[2] = '%s'\n", av[2]);
	printf("DEBUG: av[3] = '%s'\n", av[3]);
	printf("DEBUG: av[4] = '%s'\n", av[4]);
	printf("\n");
	// ====================================
	*/

	// Parsear argumentos obligatorios
	// ¿Por qué cast a (int)?
	// - ft_atol() retorna long (más seguro para detectar overflow)
	// - Pero n_philo es int en struct (suficiente para 1-200)
	simu->n_philo = (int)ft_atol(av[1]);
	simu->time_to_die = ft_atol(av[2]);
	simu->time_to_eat = ft_atol(av[3]);
	simu->time_to_sleep = ft_atol(av[4]);

	/*
	// ===== DEBUG: Ver qué parseamos =====
	printf("DEBUG: n_philo parsed = %d\n", simu->n_philo);
	printf("DEBUG: time_to_die parsed = %ld\n", simu->time_to_die);
	printf("DEBUG: time_to_eat parsed = %ld\n", simu->time_to_eat);
	printf("DEBUG: time_to_sleep parsed = %ld\n", simu->time_to_sleep);
	printf("\n");
	*/

	// ¿Por qué verificar -1 después de parsing?
	// - ft_atol() devuelve -1 en caso de error
	// - Un solo check detecta todos los errores de conversión
	if (simu->n_philo == -1 || simu->time_to_die == -1
		|| simu->time_to_eat == -1 || simu->time_to_sleep == -1)
	{
		printf("Error: Arguments must be valid positive numbers\n");
		return (false);
	}
	// Argumento opcional: número de comidas
	if (ac == 6)
	{
		simu->must_eat = (int)ft_atol(av[5]);
		if (simu->must_eat == -1)
		{
			printf("Error: number_of_times_each_philosopher_must_eat must be a valid positive number\n");
			return (false);
		}
	}
	else
	{
		// ¿Por qué -1 significa "no especificado"?
		// - -1 es imposible como valor válido (must_eat > 0)
		// - Fácil de verificar: if (simu->must_eat != -1)
		// - Alternativa: usar otro flag bool, pero -1 es más simple
		simu->must_eat = -1;
	}
	// Validar rangos
	if (!validate_args(simu))
		return (false);
	// Inicializar campos restantes
	// ¿Por qué aquí?
	// - Centralizar toda la inicialización de t_simu
	// - main() solo necesita llamar parse_args(
	simu->stop = false;
	simu->start_time = 0;	// Se inicializará justo antes de crear threads
	simu->forks = NULL;		// Se asignará en init_mutexes()
	simu->philos = NULL;	// Se asignará en init_philos()
	return (true);
}