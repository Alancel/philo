/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:05:30 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:21:57 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*runtime(void *data)
{
	t_run	*philo;

	philo = data;
	pthread_mutex_lock(&g_opts.mutex);
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
	pthread_mutex_unlock(&g_opts.mutex);
	return (NULL);
}

int	check_runtime(void)
{
	int	done;
	int	i;

	done = 0;
	while (done < g_opts.num_of_philos)
	{
		done = 0;
		i = 0;
		while (i < g_opts.num_of_philos)
		{
			if (g_run[i].status == 'm')
				done++;
			else if ((get_time() - g_run[i].last_eat
					> g_opts.time_to_die) && g_run[i].status != 'E')
			{
				g_opts.runtime = false;
				g_run[i].status = 'D';
				print(&g_run[i]);
				return (1);
			}
			i++;
		}
	}
	return (1);
}
