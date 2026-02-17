/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 10:51:50 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/17 12:08:16 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_simu	simu;

	printf("=== Testing parsing ===\n\n");
	if (!parse_args(ac, av, &simu))
	{
		printf("\nParsing failed\n");
		return (1);
	}
	printf("\nParsing successful!\n\n");
	printf("Configuration:\n");
	printf("	Philosophers:	%d\n", simu.n_philo);
	printf("	Time to die:	%ld ms\n", simu.time_to_die);
	printf("	Time to eat:	%ld ms\n", simu.time_to_eat);
	printf("	Time to sleep:	%ld ms\n", simu.time_to_sleep);
	if (simu.must_eat != -1)
		printf("	Must eat:		%d times\n", simu.must_eat);
	else
		printf("	Must eat:		(no limit)\n");
	printf("	Stop flag:		%s\n", simu.stop ? "true" : "false" );
	return (0);
}

/*
# Recompilar sin debug
gcc -Wall -Werror -Wextra -g parsing.c test_parsing.c -o test_parse

# ===== TESTS VÁLIDOS =====
echo "=== TEST 1: Caso básico ==="
./test_parse 5 800 200 200

echo -e "\n=== TEST 2: Con must_eat ==="
./test_parse 4 410 200 200 7

echo -e "\n=== TEST 3: 1 filósofo (caso especial) ==="
./test_parse 1 800 200 200

echo -e "\n=== TEST 4: Números grandes ==="
./test_parse 200 2147483647 1000 1000

echo -e "\n=== TEST 5: Con signo + ==="
./test_parse 5 +800 200 200

# ===== TESTS INVÁLIDOS (deben fallar) =====
echo -e "\n=== TEST 6: Pocos argumentos ==="
./test_parse 5 800 200

echo -e "\n=== TEST 7: Demasiados argumentos ==="
./test_parse 5 800 200 200 7 9

echo -e "\n=== TEST 8: Número negativo ==="
./test_parse 5 -800 200 200

echo -e "\n=== TEST 9: No numérico ==="
./test_parse 5 abc 200 200

echo -e "\n=== TEST 10: 0 filósofos ==="
./test_parse 0 800 200 200

echo -e "\n=== TEST 11: Demasiados filósofos ==="
./test_parse 201 800 200 200

echo -e "\n=== TEST 12: time_to_die = 0 ==="
./test_parse 5 0 200 200

echo -e "\n=== TEST 13: Overflow (INT_MAX + 1) ==="
./test_parse 5 2147483648 200 200

echo -e "\n=== TEST 14: Mezcla números y letras ==="
./test_parse 5 123abc 200 200

echo -e "\n=== TEST 15: String vacío ==="
./test_parse 5 "" 200 200

echo -e "\n=== TEST 16: Solo signo ==="
./test_parse 5 + 200 200

echo -e "\n=== TEST 17: must_eat = 0 ==="
./test_parse 5 800 200 200 0
*/