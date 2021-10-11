/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:21:42 by alancel           #+#    #+#             */
/*   Updated: 2021/10/11 19:23:54 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	thinking(t_run *philo)
{
	change_status(philo, 'T');
	print(philo);
	sem_wait(g_opts.semaphore);
}

void	take_forks(t_run *philo)
{
	sem_wait(g_semaphore);
	sem_wait(g_semaphore);
	change_status(philo, 'F');
	print(philo);
	print(philo);
	sem_post(g_opts.semaphore);
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
	sem_post(g_semaphore);
	sem_post(g_semaphore);
}

void	sleeping(t_run *philo)
{
	philo->sleep = get_time();
	change_status(philo, 'S');
	usleep(g_opts.time_to_sleep - 20000);
	while (get_time() - philo->sleep < g_opts.time_to_sleep)
		;
}