/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 20:14:35 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:12:45 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 7)
		return (error("Wrong args"));
	if (!(init_args(argc, argv)))
		return (error("Wrong args"));
	if (philo_init() || check_runtime())
	{
		pthread_mutex_unlock(&g_opts.print);
		return (1);
	}
}
