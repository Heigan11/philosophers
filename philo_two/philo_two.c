#include "philo_two.h"

int	ft_sleeping(t_philosopher philo, int *time)
{
	if (!*philo.dead)
		printf("%d philosopher %d is sleeping\n", *time, philo.name_philo);
	if (philo.time_to_sleep >= philo.time_to_die)
	{
		*time += usleep_improved(philo.time_to_die);
		sem_wait(philo.sem_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.sem_print);
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
		sem_wait(philo.sem_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.sem_print);
		*philo.dead = 1;
		sem_post(philo.sem);
		sem_post(philo.sem);
		sem_post(philo.waiter);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
		if (i == 1)
			*time += usleep_improved(philo.time_to_die - philo.time_to_eat);
		else
			*time += usleep_improved(philo.time_to_die - philo.time_to_sleep);
		sem_wait(philo.sem_print);
		if (!*philo.dead)
			printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.sem_print);
		*philo.dead = 1;
		sem_post(philo.sem);
		sem_post(philo.sem);
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
		ft_semwait(&philo);
		time = (int)(get_time() - philo.time_start);
		time -= time % 10;
		if (ft_eating(philo, &time, i))
			return (0);
		philo.time_end_eat = time;
		sem_post(philo.sem);
		sem_post(philo.sem);
		sem_post(philo.waiter);
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
	sem_t			*sem;
	sem_t			*sem_print;
	sem_t			*waiter;

	args = malloc(sizeof(t_args));
	if (!args)
		return (EXIT_FAILURE);
	if (parse_argv(args, av, ac))
		return (free_all(args, NULL, EXIT_FAILURE));
	philos = malloc(sizeof(t_philosopher) * args->num_of_philo);
	if (!philos)
		return (free_all(args, NULL, EXIT_FAILURE));
	ft_unlink();
	sem = sem_open("semaphore", O_CREAT, 0666, args->num_of_philo);
	sem_print = sem_open("sem_print", O_CREAT, 0666, 1);
	waiter = sem_open("waiter", O_CREAT, 0666, args->num_of_philo);
	if (sem == SEM_FAILED || sem_print == SEM_FAILED || waiter == SEM_FAILED)
		return (free_all(args, philos, 1) && semclose(sem, sem_print, waiter));
	philos[0].waiter = waiter;
	philos_init(args, philos, sem, sem_print);
	pthread_init(args, philos);
	semclose(sem, sem_print, waiter);
	return (free_all(args, philos, EXIT_SUCCESS));
}
