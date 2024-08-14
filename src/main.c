/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariannazhukova <mariannazhukova@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:58:42 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/14 18:03:41 by mariannazhu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
	t_env	*philo_info;
	
	philo_info = (t_env *)my_malloc(sizeof(t_env));
	if (check_arguments(argc, argv)) 
	{
		//set timestamp. write a function with gettimeoftheday
		set_arguments(argc, argv, philo_info);
		philo_info->philo_arr = (t_philo *)my_malloc(sizeof(t_philo) * (philo_info->num_philos));
		toggle_mutexes(philo_info, true);
		create_threads(philo_info, philo_info->philo_arr);
		join_threads(philo_info, philo_info->philo_arr);
		toggle_mutexes(philo_info, false);
		free(philo_info->philo_arr);
		free(philo_info);
	}
	else
	{
		free(philo_info);
		return (1);
	}
	
	return (0);
}
