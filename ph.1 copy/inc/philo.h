#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_optoions	t_opts;
typedef struct s_runtime	t_run;

struct			s_runtime
{
	pthread_t	philo;
	uint64_t	last_eat;
	uint64_t	sleep;
	char		status;
	int			pos;
	int			eat;
};

struct			s_options
{
	int				runtime;
	int				num_of_philos;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		time_to_die;
	int				eat_count;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
};

struct s_options			g_opts;
struct s_runtime			*g_run;
pthread_mutex_t				*g_forks;
uint64_t					g_start_time;

int			init_args(int argc, char **argv);
int			check_runtime(void);
int			runtime_init(void);
int			ft_atoi(char *nbr);
int			philo_init(void);
int			check_args(void);
int			error(char *str);
void		print(t_run *philo);
void		eating(t_run *philo);
void		*runtime(void *data);
void		sleeping(t_run *philo);
void		thinking(t_run *philo);
void		put_forks(t_run *philo);
void		take_forks(t_run *philo);
void		change_status(t_run *philo, char status);
char		*get_status(char status);
uint64_t	get_time(void);
#endif