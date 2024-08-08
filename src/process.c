/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 17:35:46 by mzhukova          #+#    #+#             */
/*   Updated: 2024/08/08 18:15:18 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

//states:
// 1 - eating
// 2 - sleeping
// 3 - thinking
// 4 - dead
void	print_state(int state, int index)
{
	if (state == 1)
		printf("Philo %i is eating 🍝, yum yum\n", index);
	else if (state == 2)
		printf("Philo %i is sleeping 🛌🏼💤\n", index);
	else if (state == 3)
		printf("Philo %i is thinking 💭\n", index);
	else if (state == 4)
		printf("Philo %i is dead 🪦\n", index);
	else if (state == 0)
		printf("State is not assigned\n");
}