/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/19 15:49:10 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_state(int state, int index, t_philo *philo)
{
	size_t time;

	pthread_mutex_lock(&philo->philo_info->mutex);
	time = get_current_time();
	if (philo->philo_info->all_alive)
	{
		if (state == EATING)
			printf("%zu Philo %i is eating 🍝, yum yum. Time since last meal: %zu\n", time - philo->philo_info->time_begin, index, time - philo->time_last_meal);
		else if (state == SLEEPING)
			printf("%zu Philo %i is sleeping 💤 Time since last meal: %zu\n", time - philo->philo_info->time_begin, index, time - philo->time_last_meal);
		else if (state == THINKING)
			printf("%zu Philo %i is thinking 💭 Time since last meal: %zu\n", time - philo->philo_info->time_begin, index, time - philo->time_last_meal);
		else if (state == DEAD)
			printf("%zu Philo %i is dead 🪦\n Time since last meal: %zu\n", time - philo->philo_info->time_begin, index, time - philo->time_last_meal);
		else if (state == 0)
			printf("State is not assigned\n");	
	}
	pthread_mutex_unlock(&philo->philo_info->mutex);
	return ;
}

void	*life_cycle(void *param)
{
	t_philo *philo;
	int		alive;
	
	philo = (t_philo *)param;
	if (is_one_philo(philo))
		return (param);
	while (1)
	{
		pthread_mutex_lock(&philo->philo_info->mutex);
		alive = philo->philo_info->all_alive;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		if (alive)
		{
			philo->state = eating_attempt(philo);
			if (philo->state == THINKING && philo->time_last_meal == 10)
			{
				print_state(THINKING, philo->index, philo);
			}
			if (philo->state == SLEEPING)
			{
				print_state(SLEEPING, philo->index, philo);
				ft_usleep(philo->philo_info->time_sleep);
				// print_state(THINKING, philo->index, philo);
			}
			else if (philo->state == DEAD)
			{
				//print_state(DEAD, philo->index, philo);
				return (param);
			}
		}
		else
			return (param);
	}
	return (param);
}

int	forks_are_free(t_philo *philo, t_philo *philo_arr)
{
	if (philo->index == 0)
	{
		if ((!philo_arr[1].forks_taken && !philo->forks_taken))
			return (1);
		else if (!philo_arr[philo->philo_info->num_philos - 1].forks_taken)
			return (philo->philo_info->num_philos - 1);
	}
	else if (!philo->forks_taken && (!philo_arr[philo->index - 1].forks_taken))
		return (philo->index - 1);
	else if (!philo->forks_taken && (!philo_arr[philo->index + 1].forks_taken))
		return (philo->index + 1);
	return (-1);
}

int eat_pasta(t_philo *philo, int target_index)
{
	if (philo->ate_times == philo->philo_info->num_of_times_each_eat)
		return (0);
	else
	{
		// printf("%zu Philo %i has taken forks 🍽️\n", get_current_time() - philo->philo_info->time_begin, philo->index);
		pthread_mutex_lock(&philo->philo_info->mutex);
		philo->forks_taken = true;
		philo->philo_info->philo_arr[target_index].forks_taken = true;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		print_state(EATING, philo->index, philo);
		ft_usleep(philo->philo_info->time_eat);
		philo->time_last_meal = get_current_time();
		philo->ate_times++;
		pthread_mutex_lock(&philo->philo_info->mutex);
		philo->forks_taken = false;
		philo->philo_info->philo_arr[target_index].forks_taken = false;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		philo->state = SLEEPING;
		return (1);
	}
	return (1);
}

int	eating_attempt(t_philo *philo)
{
	int		target_index;
	
	if (!is_dead(philo))
	{
		pthread_mutex_lock(&philo->philo_info->mutex);
		target_index = forks_are_free(philo, philo->philo_info->philo_arr);
		pthread_mutex_unlock(&philo->philo_info->mutex);
		if (target_index >= 0 && target_index < philo->philo_info->num_philos)
		{
			if (!eat_pasta(philo, target_index) || is_dead(philo))
				return (DEAD);
			return (SLEEPING);
		}
		else
		{
			pthread_mutex_lock(&philo->philo_info->mutex);
			philo->forks_taken = false;
			// philo->state = THINKING;
			pthread_mutex_unlock(&philo->philo_info->mutex);
			ft_usleep(1);
			return (THINKING); //thinking
		}
	}
	return (1); // eating
}

int is_one_philo(t_philo *philo)
{
	if (philo->philo_info->num_philos == 1)
	{
		ft_usleep(philo->philo_info->time_die);
		printf("Poor guy had no friends and no forks. died of starvation 🪦\n");
		return (1);
	}
	return (0);
}

//NEW PROBE FUNCTIONS
