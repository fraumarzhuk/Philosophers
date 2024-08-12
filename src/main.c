/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:58:42 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/12 14:36:55 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
	t_env	*philo_info;
	t_philo	philos[200];
	
	philo_info = malloc(sizeof(t_env));
	philo_info->philo_arr = philos;
	if (check_arguments(argc, argv))
	{
		//set timestamp. write a function with gettimeoftheday
		toggle_mutexes(philo_info, philos, true);
		set_arguments(argc, argv, philo_info);
		create_threads(philo_info, philos);
		join_threads(philo_info, philos);
		toggle_mutexes(philo_info, philos, false);
	}
	else
	{
		free(philo_info);
		return (1);
	}
	
	return (0);
}
//DELETE LEAK KILLER
// Do a linked list anyway? so they are circled?