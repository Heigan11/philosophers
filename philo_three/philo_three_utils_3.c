#include "philo_three.h"

void	ft_semwait(t_philosopher *philo)
{
	sem_wait(philo->waiter);
	sem_wait(philo->sem);
	sem_wait(philo->sem);
}

void	*ft_watcher(void *philos)
{
	t_philosopher	philo;
	int				i;

	i = 0;
	philo = *(t_philosopher *)philos;
	usleep(10000);
	sem_wait(philo.process);
	if (philo.num_must_eat && philo.num_of_philo % 2 != 0)
		usleep_improved(philo.time_to_eat * 3);
	else if (philo.num_must_eat && philo.num_of_philo % 2 == 0)
		usleep_improved(philo.time_to_eat * 2);
	while (i < philo.num_of_philo)
	{
		kill(philo.pid[i], SIGKILL);
		i++;
	}
	return (NULL);
}

void	pthread_init(t_args *args, t_philosopher *philos)
{
	int			i;
	int			status;
	pthread_t	watcher;

	pthread_create(&watcher, NULL, ft_watcher, (void *)&philos[0]);
	i = 0;
	while (i < args->num_of_philo)
	{
		philos->pid[i] = fork();
		if (philos->pid[i] == -1)
			bad_args("pthread_init() fork()");
		else if (philos->pid[i] == 0)
		{
			sem_wait(philos[i].process);
			life_cycle((void *)&philos[i]);
		}
		i++;
	}
	i = 0;
	while (i < args->num_of_philo)
	{
		waitpid(philos->pid[i], &status, 0);
		i++;
	}
	pthread_join(watcher, NULL);
}

void	ft_unlink(void)
{
	sem_unlink("semaphore");
	sem_unlink("sem_print");
	sem_unlink("waiter");
	sem_unlink("procces");
}

int	semclose(t_sem *sems)
{
	if (sems->sem)
		sem_close(sems->sem);
	if (sems->sem_print)
		sem_close(sems->sem_print);
	if (sems->waiter)
		sem_close(sems->waiter);
	if (sems->procces)
		sem_close(sems->procces);
	return (EXIT_FAILURE);
}
