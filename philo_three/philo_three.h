#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*waiter;
	sem_t			*process;
	pid_t			*pid;
}	t_philosopher;

typedef struct s_args
{
	long int		time_start;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
}	t_args;

typedef struct s_sem
{
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*waiter;
	sem_t			*procces;
}	t_sem;

int			bad_args(char *msg);
int			ft_atoi(const char *str);
long int	get_time(void);
int			usleep_improved(int time);
int			free_all(t_args *args, t_philosopher *philos,
				pid_t *pid, t_sem *sems);
void		ft_mutex_init(t_args *args, pthread_mutex_t *forks,
				pthread_mutex_t *mutex_print);
void		philos_init(t_args *args, t_philosopher *philos,
				sem_t	*sem, sem_t	*sem_print);
int			parse_argv(t_args *args, char **av, int ac);
void		ft_semwait(t_philosopher *philo);
void		ft_sempost(t_philosopher *philo);
void		*life_cycle(void *philos);
void		pthread_init(t_args *args, t_philosopher *philos);
void		ft_unlink(void);
int			semclose(t_sem *sems);
void		ft_sem_init(t_sem *sems, t_args *args);
#endif
