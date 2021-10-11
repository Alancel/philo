/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:04:25 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:14:12 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	thinking(t_run *philo)
{
	change_status(philo, 'T');
	print(philo);
}

void	take_forks(t_run *philo)
{
	pthread_mutex_unlock(&g_opts.mutex);
	change_status(philo, 'F');
	pthread_mutex_lock(&g_forks[philo->pos - 1]);
	print(philo);
	pthread_mutex_lock(&g_forks[philo->pos % g_opts.num_of_philos]);
	print(philo);
}

void	eating(t_run *philo)
{
	change_status(philo, 'E');
	print(philo);
	philo->eat++;
	philo->last_eat = get_time();
	usleep(g_opts.time_to_eat - 20000);
	while (get_time() - philo->last_eat < g_opts.time_to_eat)
		;
}

void	put_forks(t_run *philo)
{
	change_status(philo, 'S');
	print(philo);
	pthread_mutex_unlock(&g_forks[philo->pos - 1]);
	pthread_mutex_unlock(&g_forks[philo->pos % g_opts.num_of_philos]);
}

void	sleeping(t_run *philo)
{
	philo->sleep = get_time();
	change_status(philo, 'S');
	usleep(g_opts.time_to_sleep - 20000);
	while (get_time() - philo->sleep < g_opts.time_to_sleep)
		;
}
