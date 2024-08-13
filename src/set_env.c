/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:06:28 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/13 16:26:23 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int check_arguments(int argc, char **argv)
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
void set_arguments(int argc, char **argv, t_env *philo_info)
{
	philo_info->num_philos = ft_atoi(argv[1]);
	philo_info->time_die = ft_atoi(argv[2]);
	philo_info->time_eat = ft_atoi(argv[3]);
	philo_info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo_info->num_of_times_each_eat = ft_atoi(argv[5]);
	else
		philo_info->num_of_times_each_eat = -1;
}


void	create_threads(t_env *philo_info, t_philo *philos)
{
	int i;
	int	error;
	
	i = 0;
	while (i < philo_info->num_philos)
	{
		philos[i].index = i;
        philos[i].philo_info = philo_info;
        philos[i].state = 3;
        philos[i].forks_taken = false;
		philos[i].ate_times = 0;
		error = pthread_create(&philos[i].thread, NULL, life_cycle, &philos[i]);
		if (error != 0)
			printf("Error creating a thread\n");
		philos[i].index = i;
		i++;
	}
}
void join_threads(t_env *philo_info, t_philo *philos)
{
	int i;
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

void toggle_mutexes(t_env *philo_info, bool is_init)
{
	int	error;
	
	error = 0;
	if (is_init == false)
		error = pthread_mutex_destroy(&philo_info->mutex);
	else if (is_init == true)
		error = pthread_mutex_init(&philo_info->mutex, NULL);
	if (error != 0)
		printf("Mutex error\n");
}
