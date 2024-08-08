/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:06:28 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/08 15:50:19 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int check_arguments(int argc)
{
	if (argc != 6 && argc != 5)
	{
		printf("Incorrect number of arguments\n");
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
void	create_threads(t_env *philo_info, struct s_philo *philos)
{
	int i;
	
	i = 0;
	while (i < philo_info->num_philos)
	{
		pthread_create(&philos[i].thread, NULL, life_cycle, NULL);
		printf("pthread created. id: %lu\n", (unsigned long int)philos[i].thread);
		philos[i].index = i;
		i++;
	}
}
void	*life_cycle(void *param)
{
	return (param);
}