/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alancel <alancel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:52:02 by alancel           #+#    #+#             */
/*   Updated: 2021/10/12 20:53:03 by alancel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdint.h>
# include <stdbool.h>

typedef struct s_optoions	t_opts;
typedef struct s_runtime	t_run;

struct			s_runtime
{
	pthread_t	thread;
	pthread_t	run_t;
	long		last_eat;
	long		sleep;
	char		status;
	int			pos;
	int			eat;
	bool		alive;
	pid_t		pid;
};

struct			s_options
{
	int				runtime;
	int				num_of_philos;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
	int				eat_count;
	bool			stop;
	sem_t			*semaphore;
	sem_t			*print;
};

struct s_options			g_opts;
struct s_runtime			*g_run;
long						g_start_time;
sem_t						*g_semaphore;

void	runtime(void *data);
void	*check_runtime(void *data);
int		pid_kill(void);
int		error(char *str);
int		ft_atoi(char *nbr);
long	get_time(void);
char	*get_status(char status);
void	change_status(t_run *philo, char status);
int		init_args(int argc, char **argv);
int		check_args(void);
int		philo_init(void);
int		semaphore_check(void);
int		runtime_init(void);
void	print(t_run *philo);
void	eating(t_run *philo);
void	sleeping(t_run *philo);
void	thinking(t_run *philo);
void	put_forks(t_run *philo);
void	take_forks(t_run *philo);
#endif