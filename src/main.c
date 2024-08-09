/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:58:42 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/09 17:42:35 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
	t_env	*philo_info;
	t_philo	philos[200];
	
	ft_alloc_init();
	philo_info = ft_malloc(sizeof(t_env));
	if (check_arguments(argc, argv))
	{
		//set timestamp. write a function with gettimeoftheday
		set_arguments(argc, argv, philo_info);
		create_threads(philo_info, philos);
		join_threads(philo_info, philos);
	}
	else
	{
		ft_destructor();
		return (1);
	}
	ft_destructor();
	return (0);
}
//ADD A NEW VERSION OF A LEAK KILLER MARIANNA