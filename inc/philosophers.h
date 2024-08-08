/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:42:53 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/08 18:07:56 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include "../libft/libft.h"
typedef struct s_env
{
	int	num_philos;
	int	time_die;
	int time_eat;
	int time_sleep;
	int	num_of_times_each_eat;
}	t_env;

typedef struct s_philo
{
	int	index;
	int	state;
	void **status;
	pthread_t thread;
	t_env	*philo_info;
}	t_philo;


//set_env
int		check_arguments(int argc);
void	set_arguments(int argc, char **argv, t_env *philo_info);
void	create_threads(t_env *philo_info, t_philo *philos);
void	*life_cycle(void *param);
void	join_threads(t_env *philo_info, t_philo *philos);

//process
void	print_state(int state, int index);
#endif