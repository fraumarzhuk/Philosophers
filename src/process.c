/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/13 16:25:51 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//states:
// 1 - eating
// 2 - sleeping
// 3 - thinking (waiting for forks)
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
	philo_arr = philo->philo_info->philo_arr;
	
	while (1)
	{
		//usleep(400);
		if (philo->state == 3) //thinking or was sleeping last time, should try to eat
		{
			print_state(3, philo->index);	 //thinking
			//check one philo and two philos, add later
			pthread_mutex_lock(&philo->philo_info->mutex);
			target_index = forks_are_free(philo, philo->philo_info->philo_arr);
			if (target_index >= 0 && target_index < philo->philo_info->num_philos) //forks are available, went to eat
			{
				if (!eat_pasta(philo, target_index))
					return (param);
				philo->state = 2; // ate well, went to sleep;
			}
			else //went to think
			{
				philo->forks_taken = false;
				print_state(3, philo->index);	 //thinking
				//usleep(philo->philo_info->time_sleep);
				philo->state = 3;
				
			}
			pthread_mutex_unlock(&philo->philo_info->mutex);
		}
		else if (philo->state == 2) //sleeping
		{
			print_state(2, philo->index);
			usleep(philo->philo_info->time_sleep);
			philo->state = 3; //try to eat next time
		}
		// pthread_mutex_unlock(&philo->philo_info->mutex);
	}
	return (param);
}

int	forks_are_free(t_philo *philo, t_philo *philo_arr)
{

	// if (philo->philo_info->num_philos == 1)
	// {
	// 	if ((!philo->forks_taken))
	// 		return (0); // change the return value for 1 philo. return negative value and toggle
	// 	return (-1);
	// }
	//ALWAYS ON THE LEFT?
	if (philo->index == 0)
	{
		if ((!philo_arr[1].forks_taken))
			return (1);
		else if (!philo_arr[philo->philo_info->num_philos - 1].forks_taken)
			return (philo->philo_info->num_philos - 1);
	}
	else if (!philo->forks_taken && (!philo_arr[philo->index - 1].forks_taken))
		return (philo->index - 1);
	else if (!philo->forks_taken && (!philo_arr[philo->index + 1].forks_taken))
		return (philo->index + 1);
	return (-1); // all forks are taken, oopsie
}

int eat_pasta(t_philo *philo, int target_index)
{
	if (philo->ate_times == philo->philo_info->num_of_times_each_eat)
	{
		pthread_mutex_unlock(&philo->philo_info->mutex);
		//pthread_detach(philo->thread);
		return (0);
	}
	else
	{
		philo->forks_taken = true;
		philo->philo_info->philo_arr[target_index].forks_taken = true;
		// printf("philo %i has taken forks %i and %i\n", philo->index, philo->index, target_index);
		philo->state = 1;
		print_state(1, philo->index);
		philo->ate_times++;
		//printf("ate times: %i, times left: %i\n\n", philo->ate_times, philo->philo_info->num_of_times_each_eat);
		usleep(philo->philo_info->time_eat);
		philo->forks_taken = false;
		philo->philo_info->philo_arr[target_index].forks_taken = false;
		return (1);
	}
	return (1);
}