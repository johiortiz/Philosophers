/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johyorti <johyorti@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 20:39:03 by johyorti          #+#    #+#             */
/*   Updated: 2026/04/15 20:42:52 by johyorti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meals(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->simu->state_mutex);
	(*philo)->last_meal = get_time();
	(*philo)->meals_eaten++;
	pthread_mutex_unlock(&(*philo)->simu->state_mutex);
}