/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:40:45 by alancel           #+#    #+#             */
/*   Updated: 2021/10/12 20:48:58 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	print(t_run *philo)
{
	if (!g_opts.runtime)
		return ;
	sem_wait(g_opts.print);
	printf("%lu %d %s\n", (get_time() - g_start_time) / 1000,
		philo->pos, get_status(philo->status));
	if (philo->status != 'D')
		sem_post(g_opts.print);
}
