/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/13 12:34:14 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//states:
// 1 - eating
// 2 - sleeping
// 3 - thinking
// 4 - dead
void	print_state(int state, int index)
{
	if (state == 1)
		printf("Philo %i is eating 🍝, yum yum\n", index);
	else if (state == 2)
		printf("Philo %i is sleeping 🛌🏼💤\n", index);
	else if (state == 3)
		printf("Philo %i is thinking 💭\n", index);
	else if (state == 4)
		printf("Philo %i is dead 🪦\n", index);
	else if (state == 0)
		printf("State is not assigned\n");
}

void	*life_cycle(void *param)
{
	t_philo *philo;
	int		target_index;
	t_philo *philo_arr;
	
	philo = (t_philo *)param;

	
    if (!philo) {
        printf("Error: philo is NULL\n");
        return NULL;
    }
    printf("philo pointer: %p\n", (void *)philo);

    if (!philo->philo_info) {
        printf("Error: philo_info is NULL\n");
        return NULL;
    }

    philo_arr = philo->philo_info->philo_arr;
    if (!philo_arr) {
        printf("Error: philo_arr is NULL\n");
        return NULL;
    }


	// philo_arr = philo->philo_info->philo_arr;
	pthread_mutex_lock(philo->mutex);
	target_index = forks_are_free(philo, philo_arr);
	if (target_index == -1) // forks are already taken by one philo, toggle back
		philo->forks_taken = false;
	else if (target_index == -0) // forks are not taken by one philo, toggle back
		philo->forks_taken = true;
	else if (target_index >= 0)
	{
		philo->forks_taken = true;
		philo_arr[target_index].forks_taken = true;
		philo->state = 1;
		print_state(1, philo->index);
		usleep(philo->philo_info->time_eat);
		philo->forks_taken = false;
		philo_arr[target_index].forks_taken = false;
	}
	else if (target_index == -2)
	{
		philo->forks_taken = false;
		philo->state = 3;
		print_state(3, philo->index);	
	}
	pthread_mutex_unlock(philo->mutex);
	return (param);
}

int	forks_are_free(t_philo *philo, t_philo *philo_arr)
{

	if (philo->philo_info->num_philos == 1)
	{
		if ((!philo->forks_taken))
			return (0); // change the return value for 1 philo. return negative value and toggle
		return (-1);
	}
	else if (philo->index == 0)
	{
		if ((!philo_arr[1].forks_taken))
			return (1);
		else if (!philo_arr[philo->philo_info->num_philos].forks_taken)
			return (philo->philo_info->num_philos);
	}
	else if (!philo->forks_taken && (!philo_arr[philo->index - 1].forks_taken))
		return (philo->index - 1);
	else if (!philo->forks_taken && (!philo_arr[philo->index + 1].forks_taken))
		return (philo->index + 1);
	return (-2);
}

