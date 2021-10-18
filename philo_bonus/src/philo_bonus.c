/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:48:41 by alancel           #+#    #+#             */
/*   Updated: 2021/10/12 20:48:50 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 7)
		return (error("Wrong args"));
	sem_unlink("forks");
	sem_unlink("printt");
	sem_unlink("semaph");
	if (!(init_args(argc, argv)))
		return (error("Wrong args"));
	if (philo_init() || !pid_kill())
	{
		sem_unlink("forks");
		sem_unlink("printt");
		sem_unlink("semaph");
		return (0);
	}
}
