/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/15 19:13:33 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_state(int state, int index, t_philo *philo)
{
	size_t time;

	time = get_current_time();
	if (philo->philo_info->all_alive)
	{
		if (state == EATING)
			printf("%zu Philo %i is eating 🍝, yum yum\n", time, index);
		else if (state == SLEEPING)
			printf("%zu Philo %i is sleeping 💤\n", time, index);
		else if (state == THINKING)
			printf("%zu Philo %i is thinking 💭\n", time, index);
		else if (state == DEAD)
			printf("%zu Philo %i is dead 🪦\n", time, index);
		else if (state == 0)
			printf("State is not assigned\n");	
	}
	return ;
}

void	*life_cycle(void *param)
{
	t_philo *philo; 
	
	philo = (t_philo *)param;
	if (is_one_philo(philo))
		return (param);
	while (philo->philo_info->all_alive)
	{
		if (philo->state == THINKING && (!eating_attempt(philo))) // were thinking before and 
				return (param);	
		else if (philo->state == SLEEPING && !is_dead(philo))
		{
			pthread_mutex_lock(&philo->philo_info->mutex);
			print_state(SLEEPING, philo->index, philo);
			pthread_mutex_unlock(&philo->philo_info->mutex);
			ft_usleep(philo->philo_info->time_sleep);
			if (is_dead(philo))
				return (param);
			philo->state = THINKING;
			ft_usleep(100);
			print_state(3, philo->index, philo);
		}
	}
	return (param);
}

int	forks_are_free(t_philo *philo, t_philo *philo_arr)
{
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
	return (-1);
}

int eat_pasta(t_philo *philo, int target_index)
{
	if (philo->ate_times == philo->philo_info->num_of_times_each_eat || is_dead(philo))
		return (0);
	else
	{
		pthread_mutex_lock(&philo->philo_info->mutex);
		philo->forks_taken = true;
		philo->philo_info->philo_arr[target_index].forks_taken = true;
		printf("%zu Philo %i has taken forks 🍽️\n", get_current_time(), philo->index);
		print_state(EATING, philo->index, philo);
		philo->ate_times++;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		ft_usleep(philo->philo_info->time_eat);
		pthread_mutex_lock(&philo->philo_info->mutex);
		philo->time_last_meal = get_current_time();
		philo->forks_taken = false;
		philo->philo_info->philo_arr[target_index].forks_taken = false;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		return (1);
	}
	return (1);
}

int	eating_attempt(t_philo *philo)
{
	int		target_index;
	
	pthread_mutex_lock(&philo->philo_info->mutex);
	target_index = forks_are_free(philo, philo->philo_info->philo_arr);
	pthread_mutex_unlock(&philo->philo_info->mutex);
	if (target_index >= 0 && target_index < philo->philo_info->num_philos)
	{
		if (!eat_pasta(philo, target_index) || is_dead(philo))
			return (0);
		philo->state = SLEEPING;
	}
	else
	{
		pthread_mutex_lock(&philo->philo_info->mutex);
		philo->forks_taken = false;
		philo->state = THINKING;
		pthread_mutex_unlock(&philo->philo_info->mutex);
	}
	return (1);
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