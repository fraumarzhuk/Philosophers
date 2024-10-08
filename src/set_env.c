/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:06:28 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/21 15:12:05 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	check_arguments(int argc, char **argv)
{
	int	i;

	if (argc != 6 && argc != 5 && argv)
	{
		printf("Incorrect number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!argv[i][0] || (!ft_isnum(argv[i])))
		{
			printf("Incorrect arguments\n");
			return (0);
		}
		i++;
	}
	if ((ft_atoi(argv[1])) > 200 || ((ft_atoi(argv[1])) < 1))
	{
		printf("Too many or to few dudes around the table\n");
		return (0);
	}
	return (1);
}

void	set_arguments(int argc, char **argv, t_env *philo_info)
{
	philo_info->num_philos = ft_atoi(argv[1]);
	philo_info->time_die = (size_t)ft_atoi(argv[2]);
	philo_info->time_eat = (size_t)ft_atoi(argv[3]);
	philo_info->time_sleep = (size_t)ft_atoi(argv[4]);
	if (argc == 6)
		philo_info->num_of_times_each_eat = ft_atoi(argv[5]);
	else
		philo_info->num_of_times_each_eat = -1;
	philo_info->all_alive = true;
	philo_info->time_begin = get_current_time();
}

void	create_threads(t_env *philo_info, t_philo *philos)
{
	int	i;
	int	error;

	i = 0;
	while (i < philo_info->num_philos)
	{
		philos[i].index = i;
		philos[i].philo_info = philo_info;
		philos[i].state = 3;
		pthread_mutex_lock(&philo_info->mutex);
		philos[i].forks_taken = false;
		pthread_mutex_unlock(&philo_info->mutex);
		philos[i].ate_times = 0;
		philos[i].index = i;
		philos[i].time_last_meal = philo_info->time_begin;
		error = pthread_create(&philos[i].thread, NULL, life_cycle, &philos[i]);
		if (error != 0)
			printf("Error creating a thread\n");
		i++;
	}
}

void	join_threads(t_env *philo_info, t_philo *philos)
{
	int	i;
	int	error;

	i = 0;
	while (i < philo_info->num_philos)
	{
		error = pthread_join(philos[i].thread, NULL);
		if (error != 0)
			printf("Error joining a thread\n");
		i++;
	}
}

void	toggle_mutexes(t_env *philo_info, bool is_init)
{
	int	error;
	int	error2;

	error = 0;
	if (is_init == false)
	{
		error = pthread_mutex_destroy(&philo_info->mutex);
		error2 = pthread_mutex_destroy(&philo_info->write);
	}
	else if (is_init == true)
	{
		error = pthread_mutex_init(&philo_info->mutex, NULL);
		error2 = pthread_mutex_init(&philo_info->write, NULL);
	}
	if (error != 0 || error2 != 0)
		printf("Mutex error\n");
}
