/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:22:55 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/16 21:39:42 by johyorti         ###   ########.fr       */
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
	if (!str[i] == '-')	// String vacío o solo "+"
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

