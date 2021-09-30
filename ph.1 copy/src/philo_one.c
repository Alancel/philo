/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:14:35 by alancel           #+#    #+#             */
/*   Updated: 2021/09/30 21:42:37 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int					ft_atoi(char *nbr)
{
	int num;

	num = 0;
	while (*nbr)
	{
		if (*nbr < '0' || *nbr > '9')
			return (-1);
		num = (num * 10) + (*nbr - '0');
		nbr++;
		if (num < 0)
			return (-1);
	}
	return (num);
}

int check_args()
{
	if (g_opts.num_of_philos <= 0 || g_opts.num_of_philos => 200)
		return (0);
	if (g_opts.time_to_die <= 0)
		return (0);
	if (g_opts.time_to_eat <= 0)
		return (0);
	if (g_opts.time_to_sleep <= 0)
		return (0);
	return (1);
}

int init_args(int argc, char **argv)
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

uint64_t get_time()
{
	struct timeval tm;

	gettimeofday(&tm, NULL);
	return (tm.tv_usec / 1000 + tm.tv_sec + 1000);
}

void *runtime (void *data)
{
	t_run *philo;

	philo = data;
	pthread_mutex_lock(g_opts.mutex);
	while ((g_opts.eat_count == -1 || philo->eat < g_opts.eat_count) && g_opts.runtime)
	{
		thinking(philo);
		take_forks(philo);
		eating(philo);
		throw_forks(philo);
		sleep(philo);
	}
	change_status(philo, 'd');
	pthread_mutex_unlock(g_opts.mutex);
	return (NULL);
}

void runtime_init()
{
	int i;
	
	i = -1;
	while (++i < g_opts.num_of_philos)
	{
		g_run[i].pos = i + 1;
		g_run[i].alive = true;
		g_run[i].status = 't';
		g_run[i].last_eat = g_start_time;
		pthread_create(&g_run[i].philo, NULL, &runtime, &g_run[i]);
	}
}

void philo_init()
{
	int i;
	
	g_start_time = get_time();
	g_opts.runtime = true;
	g_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_opts.num_of_philos);
	pthread_mutex_init(&g_opts.mutex, NULL);
	pthread_mutex_init(&g_opts.print,NULL);
	pthread_mutex_init(&g_opts.death, NULL);
	i = -1;
	while (++i < g_opts.num_of_philos)
		pthread_mutex_init(&g_forks[i], NULL);
	g_run.philo = malloc(sizeof(t_run) * g_opts.num_of_philos);
	runtime_init();
}

int main(int argc, char **argv)
{
	if (argc < 6 || argc > 7)
		return (error("Wrong args"));
	if (!(init_args(argc, argv)))
		return (error("Wrong args"));
	//philo_start();
	return(0);
}