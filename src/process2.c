/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:30:50 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/14 14:38:40 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// void	print_state(int state, int index)
// {
// 	if (state == EATING)
// 		printf("Philo %i is eating 🍝, yum yum\n", index);
// 	else if (state == SLEEPING)
// 		printf("Philo %i is sleeping 💤\n", index);
// 	else if (state == THINKING)
// 		printf("Philo %i is thinking 💭\n", index);
// 	else if (state == DEAD)
// 		printf("Philo %i is dead 🪦\n", index);
// 	else if (state == 0)
// 		printf("State is not assigned\n");
// }

// void	*life_cycle(void *param)
// {
// 	t_philo *philo;
// 	t_philo *philo_arr;
	
// 	philo = (t_philo *)param;
// 	philo_arr = philo->philo_info->philo_arr;
	
// 	if (philo->philo_info->num_philos == EATING)
// 	{
// 		usleep(philo->philo_info->time_die);
// 		printf("Poor guy had no friends and no forks. died of starvation and misery🪦\n");
// 		return (param);
// 	}
// 	while (1)
// 	{
// 		//2 or more than 2 philos
// 		int 
// 	}
// 	return (param);
// }