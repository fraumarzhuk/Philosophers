/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:06:28 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/09 17:33:33 by mzhukova         ###   ########.fr       */
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
		printf("Too many  or to few dudes around the table\n");
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
		philo_info->num_of_times_each_eat = 0;
}
void	create_threads(t_env *philo_info, t_philo *philos)
{
	int i;
	int	error;
	
	i = 1;
	while (i <= philo_info->num_philos)
	{
		error = pthread_create(&philos[i].thread, NULL, life_cycle, &philos[i]);
		if (error != 0)
			printf("Error creating a thread\n");
		//printf("pthread created. id: %lu\n", (unsigned long int)philos[i].thread);
		philos[i].index = i;
		// printf("philo state: %i and index: %i\n", philos[i].state, philos[i].index);
		i++;
	}
}
void join_threads(t_env *philo_info, t_philo *philos)
{
	int i;
	int	error;
	
	i = 1;
	while (i <= philo_info->num_philos)
	{
		error = pthread_join(philos[i].thread, philos[i].status);
		if (error != 0)
			printf("Error joining a thread\n");
		i++;
	}
}

void	*life_cycle(void *param)
{
	t_philo *philo;
	
	philo = param;
	// printf("thread %lu has started!\n", philo->thread);
	// printf("philo state: %i and index: %i\n", philo->state, philo->index);
	// print_state(philo->state, philo->index);
	
	//1. check the forks on left and right
	//2. if forks are free, take
	//3. if forks are taken, eat while time_eat--
	//4. when finished eating, start thinking or sleeping, unlock the forks, times_of eat--
	//(save num_eat to each philo?)
	//(how to choose to sleep or to think?)
	//5.
	return (param);
}