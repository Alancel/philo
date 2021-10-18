/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:00:55 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:21:42 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	runtime_init(void)
{
	int	i;

	i = 0;
	while (i < g_opts.num_of_philos)
	{
		g_run[i].pos = i + 1;
		g_run[i].status = 'T';
		g_run[i].last_eat = g_start_time;
		if (pthread_create(&g_run[i].philo, NULL, &runtime, &g_run[i]))
			return (0);
		i++;
	}
	return (1);
}

int	philo_init(void)
{
	int	i;

	g_start_time = get_time();
	g_opts.runtime = true;
	g_forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * g_opts.num_of_philos);
	if (!g_forks)
		return (0);
	if (pthread_mutex_init(&g_opts.mutex, NULL)
		|| pthread_mutex_init(&g_opts.print, NULL)
		|| pthread_mutex_init(&g_opts.death, NULL))
		return (0);
	i = 0;
	while (i < g_opts.num_of_philos)
		pthread_mutex_init(&g_forks[i++], NULL);
	g_run = malloc(sizeof(t_run) * g_opts.num_of_philos);
	if (runtime_init())
		return (0);
	return (1);
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
