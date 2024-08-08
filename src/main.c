/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:58:42 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/08 17:33:58 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int main(int argc, char **argv)
{
	t_env	*philo_info;
	t_philo	philos[200];
	
	philo_info = ft_malloc(sizeof(t_env *));
	if (check_arguments(argc))
	{
		set_arguments(argc, argv, philo_info);
		create_threads(philo_info, philos);
		join_threads(philo_info, philos);
	}
	else
		return (1);
	return (0);
}