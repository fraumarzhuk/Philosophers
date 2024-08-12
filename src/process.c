/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/12 14:58:54 by mzhukova         ###   ########.fr       */
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
	
	philo = param;
	if (philo->mutex == NULL)
    {
        printf("Mutex is not initialized\n");
        return NULL;
    }
	pthread_mutex_lock(philo->mutex);
	if (forks_are_free(philo))
	{
		philo->forks_taken = true;
		philo->state = 1;
		print_state(1, philo->index);
		usleep(philo->philo_info->time_eat);
		philo->forks_taken = false;
	}
	else
		print_state(3, philo->index);	
	pthread_mutex_unlock(philo->mutex);
	// printf("thread %lu has started!\n", philo->thread);
	// printf("philo state: %i and index: %i\n", philo->state, philo->index);
	// print_state(philo->state, philo->index);
	
	//1. check the forks on left and right
	//2. if forks are free, take
	//3. if forks are taken, eat while time_eat--
	//4. when finished eating, start thinking or sleeping, unlock the forks, times_of eat--
	//(save num_eat to each philo?)
	//(how to choose to sleep or to think?)
	return (param);
}

int	forks_are_free(t_philo *philo)
{
	t_philo *philo_arr;

	philo_arr = philo->philo_info->philo_arr;
	if (philo->philo_info->num_philos == 1)
	{
		if ((!philo->forks_taken))
			return (1);
		return (0);
	}
	else if (philo->index == 0)
	{
		if ((!philo_arr[1].forks_taken) && (!philo_arr[philo->philo_info->num_philos].forks_taken))
			return (1);
	}
	else if ((!philo_arr[philo->index - 1].forks_taken) && (!philo_arr[philo->index + 1].forks_taken))
		return (1);
	return (0);
}