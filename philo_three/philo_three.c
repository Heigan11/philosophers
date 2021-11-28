#include "philo_three.h"

int	ft_sleeping(t_philosopher philo, int *time)
{
	sem_wait(philo.sem_print);
	printf("%d philosopher %d is sleeping\n", *time, philo.name_philo);
	sem_post(philo.sem_print);
	if (philo.time_to_sleep >= philo.time_to_die)
	{
		*time += usleep_improved(philo.time_to_die);
		sem_wait(philo.sem_print);
		printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.process);
		exit (1);
	}
	*time += usleep_improved(philo.time_to_sleep);
	sem_wait(philo.sem_print);
	printf("%d philosopher %d is thinking\n", *time, philo.name_philo);
	sem_post(philo.sem_print);
	return (0);
}

void	long_time_eat(t_philosopher philo, int *time)
{
	if (philo.time_to_eat > philo.time_to_die)
	{
		*time += usleep_improved(philo.time_to_die);
		sem_wait(philo.sem_print);
		printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.sem);
		sem_post(philo.sem);
		sem_post(philo.waiter);
		sem_post(philo.process);
		exit (EXIT_FAILURE);
	}
}

int	ft_eating(t_philosopher philo, int *time, int i)
{
	sem_wait(philo.sem_print);
	printf("%d philosopher %d has taken a fork\n", *time, philo.name_philo);
	printf("%d philosopher %d is eating\n", *time, philo.name_philo);
	sem_post(philo.sem_print);
	long_time_eat(philo, time);
	if ((*time - philo.time_end_eat) + philo.time_to_eat > philo.time_to_die)
	{
		if (i == 1)
			*time += usleep_improved(philo.time_to_die - philo.time_to_eat);
		else
			*time += usleep_improved(philo.time_to_die - philo.time_to_sleep);
		sem_wait(philo.sem_print);
		printf("%d philosopher %d died\n", *time, philo.name_philo);
		sem_post(philo.sem);
		sem_post(philo.sem);
		sem_post(philo.process);
		exit (1);
	}
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
	while ((philo.num_must_eat > 0 || philo.infinity))
	{
		ft_semwait(&philo);
		time = (int)(get_time() - philo.time_start);
		time -= time % 10;
		ft_eating(philo, &time, i);
		philo.time_end_eat = time;
		ft_sempost(&philo);
		philo.num_must_eat--;
		if (philo.num_must_eat == 0 && !philo.infinity)
		{
			sem_post(philo.process);
			exit (0);
		}
		ft_sleeping(philo, &time);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args			*args;
	t_philosopher	*philos;
	t_sem			*sems;
	pid_t			*pid;

	args = malloc(sizeof(t_args));
	sems = malloc(sizeof(t_sem));
	parse_argv(args, av, ac);
	pid = malloc(sizeof(pid_t) * args->num_of_philo);
	philos = malloc(sizeof(t_philosopher) * args->num_of_philo);
	if (!philos || !args || !sems || !pid)
		return (free_all(args, philos, pid, sems));
	ft_unlink();
	ft_sem_init(sems, args);
	philos[0].waiter = sems->waiter;
	philos[0].process = sems->procces;
	philos[0].pid = pid;
	philos_init(args, philos, sems->sem, sems->sem_print);
	pthread_init(args, philos);
	semclose(sems);
	return (free_all(args, philos, pid, sems));
}
