/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:02:56 by alancel           #+#    #+#             */
/*   Updated: 2021/10/08 19:17:33 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	error(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	ft_atoi(char *nbr)
{
	int	num;

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

uint64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (uint64_t)1000000 + time.tv_usec);
}

char	*get_status(char status)
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

void	change_status(t_run *philo, char status)
{
	if (philo->status != 'D')
		philo->status = status;
}
