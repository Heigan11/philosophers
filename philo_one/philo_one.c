#include "philo_one.h"

int	ft_sleeping(t_philosopher philo, int *time)
{
	if (!*philo.dead)
		printf("%d philosopher %d is sleeping\n", *time, philo.name_philo);
	if (philo.time_to_sleep > philo.time_to_die)
	{
		*time += usleep_improved(philo.time_to_die);
		pthread_mutex_lock(philo.mutex_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		pthread_mutex_unlock(philo.mutex_print);
		*philo.dead = 1;
		return (1);
	}
	if (!*philo.dead)
		*time += usleep_improved(philo.time_to_sleep);
	if (!*philo.dead)
		printf("%d philosopher %d is thinking\n", *time, philo.name_philo);
	return (0);
}

int	long_time_eat(t_philosopher philo, int *time)
{
	if (philo.time_to_eat > philo.time_to_die)
	{
		*time += usleep_improved(philo.time_to_die);
		pthread_mutex_lock(philo.mutex_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		*philo.dead = 1;
		pthread_mutex_unlock(philo.mutex_print);
		ft_mutex_unlock(philo);
		return (1);
	}
	return (0);
}

int	ft_eating(t_philosopher philo, int *time, int i)
{
	if (!*philo.dead)
	{
		printf("%d philosopher %d has taken a fork\n", *time, philo.name_philo);
		printf("%d philosopher %d is eating\n", *time, philo.name_philo);
	}
	if (long_time_eat(philo, time))
		return (1);
	if ((*time - philo.time_end_eat) + philo.time_to_eat > philo.time_to_die)
	{
		*time += usleep_improved((philo.time_to_die * i - philo.time_to_eat * i
					- philo.time_to_sleep * (i - 1)) / i);
		pthread_mutex_lock(philo.mutex_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		pthread_mutex_unlock(philo.mutex_print);
		*philo.dead = 1;
		ft_mutex_unlock(philo);
		return (1);
	}
	if (!*philo.dead)
		*time += usleep_improved(philo.time_to_eat);
	return (0);
}

void	*life_cycle(void *philos)
{
	t_philosopher	philo;
	int				time;
	int				i;

	philo = *(t_philosopher *)philos;
	i = 1;
	while ((philo.num_must_eat > 0 || philo.infinity) && !*philo.dead)
	{
		ft_mutex_lock(philo);
		time = (int)(get_time() - philo.time_start);
		time -= time % 10;
		if (ft_eating(philo, &time, i))
			return (0);
		philo.time_end_eat = time;
		ft_mutex_unlock(philo);
		philo.num_must_eat--;
		if (philo.num_must_eat == 0)
			break ;
		if (ft_sleeping(philo, &time))
			return (0);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args			*args;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_print;

	args = malloc(sizeof(t_args));
	if (!args)
		return (EXIT_FAILURE);
	if (parse_argv(args, av, ac))
		return (free_all(args, NULL, NULL, EXIT_FAILURE));
	philos = malloc(sizeof(t_philosopher) * args->num_of_philo);
	if (!philos)
		return (free_all(args, NULL, NULL, EXIT_FAILURE));
	forks = malloc(sizeof(pthread_mutex_t) * args->num_of_philo);
	if (!forks)
		return (free_all(args, philos, NULL, EXIT_FAILURE));
	ft_mutex_init(args, forks, &mutex_print);
	philos_init(args, philos, forks, &mutex_print);
	pthread_init(args, philos);
	return (free_all(args, philos, forks, EXIT_SUCCESS));
}
