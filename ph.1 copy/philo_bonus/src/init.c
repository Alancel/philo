/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:53:51 by alancel           #+#    #+#             */
/*   Updated: 2021/10/11 20:26:02 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_args(int argc, char **argv)
{
	g_opts.num_of_philos = ft_atoi(argv[1]);
	g_opts.time_to_die = ft_atoi(argv[2]) * 1000;
	g_opts.time_to_eat = ft_atoi(argv[3]) * 1000;
	g_opts.time_to_sleep = ft_atoi(argv[4]) * 1000;
	g_opts.eat_count = -1;
	if (argc == 6)
	{
		g_opts.eat_count = ft_atoi(argv[5]);
		if (g_opts.eat_count <= 0)
			return (0);
	}
	return (check_args());
}

int	check_args(void)
{
	if (g_opts.num_of_philos <= 0 || g_opts.num_of_philos >= 200)
		return (0);
	if (g_opts.time_to_die <= 0)
		return (0);
	if (g_opts.time_to_eat <= 0)
		return (0);
	if (g_opts.time_to_sleep <= 0)
		return (0);
	return (1);
}

int	philo_init(void)
{
	g_start_time = get_time();
	g_opts.runtime = true;
	g_semaphore = sem_open("forks", O_CREAT, S_IRWXG, g_opts.num_of_philos);
	g_opts.print = sem_open("print", O_CREAT, S_IRWXG, 1);
	g_opts.semaphore = sem_open("semaphore", O_CREAT, S_IRWXG, 1);
	if (!(g_run = malloc(sizeof(t_run) * g_opts.num_of_philos)))
		return (1);
	if (semaphore_check() || runtime_init())
		return (1);
	return (0);
}

int	semaphore_check(void)
{
	if (g_semaphore == SEM_FAILED)
		return (1);
	if (g_opts.print == SEM_FAILED)
		return (1);
	if (g_opts.semaphore == SEM_FAILED)
		return (1);
	return (0);
}

int	runtime_init(void)
{
	int	i;

	i = 0;
	while (i < g_opts.num_of_philos)
	{
		g_run[i].pos = i + 1;
		g_run[i].alive = false;
		g_run[i].status = 'T';
		g_run[i].eat = 0;
		g_run[i].last_eat = g_start_time;
		if ((g_run[i].pid = fork()) == 0)
			runtime(&g_run[i]);
		else if (g_run[i].pid < 0)
			return (1);
		i++;
	}
	return (0);
}
