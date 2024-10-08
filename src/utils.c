/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:15:40 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/21 15:10:21 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

// gettimeofthe day
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Get time error \n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(milliseconds);
	return (0);
}

int	is_dead(t_philo *philo)
{
	size_t	now;
	size_t	time_last_meal;
	size_t	time_die;

	now = get_current_time();
	time_last_meal = philo->time_last_meal;
	time_die = philo->philo_info->time_die;
	if ((now - time_last_meal) >= time_die)
	{
		pthread_mutex_lock(&philo->philo_info->mutex);
		print_state(DEAD, philo->index, philo);
		philo->philo_info->all_alive = false;
		pthread_mutex_unlock(&philo->philo_info->mutex);
		return (1);
	}
	return (0);
}

int	is_one_philo(t_philo *philo)
{
	if (philo->philo_info->num_philos == 1)
	{
		ft_usleep(philo->philo_info->time_die);
		printf("Poor guy had no friends and no forks. died of starvation 🪦\n");
		return (1);
	}
	return (0);
}

int	dead_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_info->mutex);
	if (!philo->philo_info->all_alive)
	{
		pthread_mutex_unlock(&philo->philo_info->mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->philo_info->mutex);
	return (1);
}
