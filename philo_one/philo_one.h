#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher
{
	long int		time_start;
	long int		time_end_eat;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				infinity;
	int				name_philo;
	int				*dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_print;
	pthread_t		philo_thread;
}	t_philosopher;

typedef struct s_args
{
	long int		time_start;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				dead;
}	t_args;

int			bad_args(char *msg);
int			ft_atoi(const char *str);
long int	get_time(void);
int			usleep_improved(int time);
int			free_all(t_args *args, t_philosopher *philos,
				pthread_mutex_t *forks, int exit_code);
void		ft_mutex_init(t_args *args, pthread_mutex_t *forks,
				pthread_mutex_t *mutex_print);
void		philos_init(t_args *args, t_philosopher *philos,
				pthread_mutex_t *forks, pthread_mutex_t *mutex_print);
int			parse_argv(t_args *args, char **av, int ac);
void		ft_mutex_lock(t_philosopher philo);
void		ft_mutex_unlock(t_philosopher philo);
void		pthread_init(t_args *args, t_philosopher *philos);
void		*life_cycle(void *philos);
#endif
