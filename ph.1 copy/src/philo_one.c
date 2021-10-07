/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:14:35 by alancel           #+#    #+#             */
/*   Updated: 2021/10/07 21:29:32 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void change_status(t_run *philo, char status);
int			doctor(void);

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
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (uint64_t)1000000 + time.tv_usec);
}


char *get_status(char status)
{
	if (status == 'D')
		return ("died");
	if (status == 'E')
		return ("is eating");
	if (status == 'T')
		return ("is thinking");
	if (status == 'S')
		return ("is sleeping");
	if (status == 'F')
		return ("has taken a fork");
	return (" ");
}

void print(t_run *philo)
{
	pthread_mutex_lock(&g_opts.print);
		printf("%llu %d %s\n", (get_time() - g_start_time) / 1000, philo->pos, get_status(philo->status));
	if (philo->status != 'D')
		pthread_mutex_unlock(&g_opts.print);
}

void change_status(t_run *philo, char status)
{
	if (philo->status != 'D')
		philo->status = status;
}

void thinking(t_run *philo)
{
	change_status(philo, 'T');
	print(philo);
}

void take_forks(t_run *philo)
{
	pthread_mutex_unlock(&g_opts.mutex);
	change_status(philo, 'F');
	pthread_mutex_lock(&g_forks[philo->pos - 1]);
	print(philo);
	pthread_mutex_lock(&g_forks[philo->pos % g_opts.num_of_philos]);
	print(philo);
}

void eating(t_run *philo)
{
	change_status(philo, 'E');
	print(philo);
	philo->eat++;
	philo->last_eat = get_time();
	usleep(g_opts.time_to_eat - 20000);
	while (get_time() - philo->last_eat < g_opts.time_to_eat)
		;
}

void put_forks(t_run *philo)
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

void *runtime (void *data)
{
	t_run *philo;

	philo = data;
	pthread_mutex_lock(&g_opts.mutex);
	while ((g_opts.eat_count == -1 || philo->eat < g_opts.eat_count) && g_opts.runtime)
	{
		thinking(philo);
		take_forks(philo);
		eating(philo);
		put_forks(philo);
		sleeping(philo);
	}
	change_status(philo, 'm');
	pthread_mutex_unlock(&g_opts.mutex);
	return (NULL);
}

int runtime_init()
{
	int i;
	
	i = 0;
	while (i < g_opts.num_of_philos)
	{
		g_run[i].pos = i + 1;
		g_run[i].alive = TRUE;
		g_run[i].status = 'T';
		g_run[i].last_eat = g_start_time;
		if(pthread_create(&g_run[i].philo, NULL, &runtime, &g_run[i]))
			return (0);
		i++;
	}
	return (1);
}

int philo_init(void)
{
	int i;
	
	g_start_time = get_time();
	g_opts.runtime = TRUE;
	g_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * g_opts.num_of_philos);
	if (pthread_mutex_init(&g_opts.mutex, NULL) ||
	pthread_mutex_init(&g_opts.print,NULL) ||
	pthread_mutex_init(&g_opts.death, NULL))
		return (0);
	i = 0;
	while (i < g_opts.num_of_philos)
		pthread_mutex_init(&g_forks[i++], NULL);
	g_run = malloc(sizeof(t_run) * g_opts.num_of_philos);
	if (runtime_init())
		return (0);
	return (1);
}

int main(int argc, char **argv)
{
	if (argc < 5 || argc > 7)
		return (error("Wrong args"));
	if (!(init_args(argc, argv)))
		return (error("Wrong args"));
	if (philo_init() || doctor())
	{
		pthread_mutex_unlock(&g_opts.print);
		return (1);
	}
}

int			doctor(void)
{
	int done;
	int i;

	done = 0;
	while (done < g_opts.num_of_philos)
	{
		done = 0;
		i = 0;
		while (i < g_opts.num_of_philos)
		{
			if (g_run[i].status == 'm')
				done++;
			else if ((get_time() - g_run[i].last_eat >
			g_opts.time_to_die) && g_run[i].status != 'E')
			{
				g_opts.runtime = FALSE;
				g_run[i].status = 'D';
				print(&g_run[i]);
				return (1);
			}
			i++;
		}
	}
	return (1);
}