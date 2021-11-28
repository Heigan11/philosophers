#include "philo_three.h"

int	free_all(t_args *args, t_philosopher *philos, pid_t *pid, t_sem *sems)
{
	if (args)
		free(args);
	if (philos)
		free(philos);
	if (pid)
		free(pid);
	if (sems)
		free(sems);
	return (EXIT_SUCCESS);
}

void	philos_init(t_args *args, t_philosopher *philos,
			sem_t	*sem, sem_t	*sem_print)
{
	int	i;

	i = -1;
	while (++i < args->num_of_philo)
	{
		philos[i].time_start = args->time_start;
		philos[i].num_of_philo = args->num_of_philo;
		philos[i].time_to_die = args->time_to_die;
		philos[i].time_to_eat = args->time_to_eat;
		philos[i].time_to_sleep = args->time_to_sleep;
		philos[i].num_must_eat = args->num_must_eat;
		philos[i].infinity = 0;
		if (!args->num_must_eat)
			philos[i].infinity = 1;
		philos[i].name_philo = i + 1;
		philos[i].time_end_eat = 0;
		philos[i].sem = sem;
		philos[i].sem_print = sem_print;
		if (i != 0)
		{
			philos[i].waiter = philos[0].waiter;
			philos[i].process = philos[0].process;
			philos[i].pid = philos[0].pid;
		}
	}
}

void	ft_sem_init(t_sem *sems, t_args *args)
{
	sems->sem = sem_open("semaphore", O_CREAT, 0666, args->num_of_philo);
	sems->sem_print = sem_open("sem_print", O_CREAT, 0666, 1);
	if (args->num_of_philo != 2)
		sems->waiter = sem_open("waiter", O_CREAT, 0666,
				args->num_of_philo - 2);
	else
		sems->waiter = sem_open("waiter", O_CREAT, 0666,
				args->num_of_philo - 1);
	sems->procces = sem_open("procces", O_CREAT, 0666, args->num_of_philo);
	if (sems->sem == SEM_FAILED || sems->sem_print == SEM_FAILED
		|| sems->waiter == SEM_FAILED || sems->procces == SEM_FAILED)
	{
		semclose(sems);
		exit(EXIT_FAILURE);
	}
}

int	parse_argv(t_args *args, char **av, int ac)
{
	if (ac <= 4 || ac > 6)
		return (bad_args("Wrong number of arguments."));
	args->num_of_philo = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->num_of_philo <= 1 || args->num_of_philo > 50
		|| args->time_to_die <= 0
		|| args->time_to_eat <= 0 || args->time_to_sleep <= 0)
		return (bad_args("Wrong value of argument/arguments."));
	if (ac == 6)
	{
		args->num_must_eat = ft_atoi(av[5]);
		if (args->num_must_eat <= 0)
			return (bad_args("Wrong value of argument/arguments."));
	}
	else
		args->num_must_eat = 0;
	args->time_start = get_time();
	return (EXIT_SUCCESS);
}

void	ft_sempost(t_philosopher *philo)
{
	sem_post(philo->waiter);
	sem_post(philo->sem);
	sem_post(philo->sem);
}
