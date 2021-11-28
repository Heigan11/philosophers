#include "philo_three.h"

int	bad_args(char *msg)
{
	printf("Error!\n%s\n", msg);
	exit (EXIT_FAILURE);
}

static int	first_simbols(const char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\f'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	res = 0;
	sign = 1;
	i = first_simbols(str);
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res * sign < 0 && sign > 0)
		return (-1);
	if (res * sign > 0 && sign < 0)
		return (0);
	return (res * sign);
}

long int	get_time(void)
{
	struct timeval		tv;
	struct timezone		tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	usleep_improved(int time)
{
	long int	time_start;
	int			time_end;

	time_start = get_time();
	usleep(time * 1000 - 10000);
	while (get_time() - time_start < time)
		usleep(100);
	time_end = get_time() - time_start;
	time_end -= time_end % 10;
	return (time_end);
}
