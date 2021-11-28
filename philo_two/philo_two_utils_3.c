#include "philo_two.h"

void	ft_semwait(t_philosopher *philo)
{
	sem_wait(philo->waiter);
	sem_wait(philo->sem);
	sem_wait(philo->sem);
}

void	pthread_init(t_args *args, t_philosopher *philos)
{
	int	i;

	i = 1;
	while (i < args->num_of_philo)
	{
		pthread_create(&philos[i].philo_thread, NULL,
			life_cycle, (void *)&philos[i]);
		i += 2;
	}
	usleep_improved(args->time_to_eat / 2);
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_create(&philos[i].philo_thread, NULL,
			life_cycle, (void *)&philos[i]);
		i += 2;
	}
	i = 0;
	while (i < args->num_of_philo)
	{
		pthread_join(philos[i].philo_thread, NULL);
		i++;
	}
}

void	ft_unlink(void)
{
	sem_unlink("semaphore");
	sem_unlink("sem_print");
	sem_unlink("waiter");
}

int	semclose(sem_t *sem, sem_t *sem_print, sem_t *waiter)
{
	if (sem)
		sem_close(sem);
	if (sem_print)
		sem_close(sem_print);
	if (waiter)
		sem_close(waiter);
	return (EXIT_FAILURE);
}
