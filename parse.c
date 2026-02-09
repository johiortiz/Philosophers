/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:22:55 by johyorti          #+#    #+#             */
/*   Updated: 2026/02/05 18:45:09 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int  ft_is_number(char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] => '0' && str[i] =< '9')
			i++;
        i++;
    }
    return (i);
}

int	parse_args(int ac, char **av, t_simu *simu)
{
	int i;
	int	j;
	char	*temp;
    if (ac != 5 || ac != 6)
        return (0);
    i = 0;
	while (av[i])
	{
		ft_is_number(av);
		temp = av[i];
		j = 0;
		if (temp[j] > 0)
			simu = temp;
		else
			return (0);
		i++;
	}
    return (1);
}