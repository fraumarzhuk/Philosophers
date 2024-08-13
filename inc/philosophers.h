/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhukova <mzhukova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:42:53 by mariannazhu       #+#    #+#             */
/*   Updated: 2024/08/13 17:43:11 by mzhukova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
// # define _ALL_SOURCE

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/libft.h"

typedef struct s_env t_env;

typedef struct s_philo
{
	int	index;
	int	state;
	int	ate_times;
	bool	forks_taken;
	//void **status;
	pthread_t thread;
	t_env	*philo_info;
}	t_philo;

//states:
// 1 - eating
// 2 - sleeping
// 3 - thinking (waiting for forks)
// 4 - dead

typedef struct s_env
{
	int	time_stamp;
	int	num_philos;
	int	time_die;
	int time_eat;
	int time_sleep;
	int	num_of_times_each_eat;
	struct timeval start;
	struct timeval end;
	unsigned long exec_usec;
	t_philo *philo_arr;
	pthread_mutex_t	mutex;
}	t_env;


//set_env
int		check_arguments(int argc, char **argv);
void	set_arguments(int argc, char **argv, t_env *philo_info);
void	create_threads(t_env *philo_info, t_philo *philos);
void	join_threads(t_env *philo_info, t_philo *philos);
void	toggle_mutexes(t_env *philo_info, bool is_init);

//process
void	print_state(int state, int index);
void	*life_cycle(void *param);
int		forks_are_free(t_philo *philo, t_philo *philo_arr);
int		eat_pasta(t_philo *philo, int target_index);
#endif
