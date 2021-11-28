#include "philo_two.h"

int	free_all(t_args *args, t_philosopher *philos, int exit_code)
{
	if (args)
		free(args);
	if (philos)
		free(philos);
	return (exit_code);
}

void	philos_init(t_args *args, t_philosopher *philos,
			sem_t	*sem, sem_t	*sem_print)
{
	int	i;

	i = 0;
	while (i < args->num_of_philo)
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
		philos[i].dead = &args->dead;
		philos[i].sem = sem;
		philos[i].sem_print = sem_print;
		i++;
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
	if (args->num_of_philo <= 1 || args->time_to_die <= 0
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
	args->dead = 0;
	return (EXIT_SUCCESS);
}
