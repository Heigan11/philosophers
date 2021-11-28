#include "philo_one.h"

void	ft_mutex_lock(t_philosopher philo)
{
	pthread_mutex_lock(philo.forks + (philo.name_philo - 1));
	if (philo.name_philo < philo.num_of_philo)
		pthread_mutex_lock(philo.forks + philo.name_philo);
	else if (philo.name_philo >= philo.num_of_philo
		&& philo.num_of_philo % 2 != 0)
		pthread_mutex_lock(philo.forks);
}

void	ft_mutex_unlock(t_philosopher philo)
{
	pthread_mutex_unlock(philo.forks + (philo.name_philo - 1));
	if (philo.name_philo < philo.num_of_philo)
		pthread_mutex_unlock(philo.forks + philo.name_philo);
	else if (philo.name_philo >= philo.num_of_philo
		&& philo.num_of_philo % 2 != 0)
		pthread_mutex_unlock(philo.forks);
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
	usleep(2000);
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
