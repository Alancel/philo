/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:06:20 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:13:28 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print(t_run *philo)
{
	pthread_mutex_lock(&g_opts.print);
	printf("%llu %d %s\n", (get_time() - g_start_time) / 1000,
		philo->pos, get_status(philo->status));
	if (philo->status != 'D')
		pthread_mutex_unlock(&g_opts.print);
}
