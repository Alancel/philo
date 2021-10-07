#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdlib.h> 
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <string.h>
#define TRUE 1
#define FALSE 0


typedef struct s_optoions	t_opts;
typedef struct s_runtime	t_run;


struct			s_runtime
{
	pthread_t philo;
	uint64_t last_eat;
	uint64_t sleep;
	bool alive;
	char status;
	int pos;
	int eat;
};

struct			s_options
{
	int		runtime;
	int			num_of_philos;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	uint64_t	time_to_die;
	int			eat_count;
	pthread_mutex_t	mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
};
struct s_options			g_opts;
struct s_runtime			*g_run;
pthread_mutex_t 			*g_forks;
uint64_t					g_start_time;

#endif