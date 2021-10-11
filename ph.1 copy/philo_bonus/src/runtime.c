/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 19:14:09 by alancel           #+#    #+#             */
/*   Updated: 2021/10/11 21:45:45 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	runtime(void *data)
{
	t_run	*philo;

	philo = data;
	if (pthread_create(&philo->thread, NULL, check_runtime, philo))
		exit(1);
	while ((g_opts.eat_count == -1 || philo->eat < g_opts.eat_count)
		&& g_opts.runtime)
	{
		thinking(philo);
		take_forks(philo);
		eating(philo);
		put_forks(philo);
		sleeping(philo);
	}
	change_status(philo, 'm');
	exit(0);
}

void	*check_runtime(void *data)
{
	t_run		*philo;

	philo = data;
	while (philo->status != 'm')
	{
		if ((philo->status != 'E' && (get_time() - philo->last_eat) > g_opts.time_to_die) || philo->alive)
		{
			philo->status = 'D';
			print(philo);
			g_opts.runtime = false;
			exit(2);
		}
	}
	return (NULL);
}

int pid_kill(void)
{
	int i;
	int j;
	int tmp;

	i = 0;
	while (i < g_opts.num_of_philos)
	{
		waitpid(-1, &tmp, 0);
		if (WEXITSTATUS(tmp) == 2)
		{
			j = 0;
			while (j < g_opts.num_of_philos)
				kill(g_run[j++].pid, SIGKILL);
			return (0);
		}
		i++;
	}
	return(0);
}