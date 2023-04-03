#include "../philo.h"

static int	ft_atoi(char *str)
{
	int i;
	int	res;

	i = 0;
	res = 0;
	while ('0' <= str[i] && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if (res & MIN_INT != 0)
			return (-1);
	}
	if (!i && !str[i])
		return (-1);
	if (!('0' <= str[i] && str[i] <= '9') && str[i])
		return (-1);
	return (res);
}

int	validate_info(int ac, char **av, t_info *info)
{
	info->num = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		info->must_eat = ft_atoi(av[5]);
		if (!info->must_eat)
			return (0);
	}
	else
		info->must_eat = 0;
	if (info->num <= 0 || info->t_die > MAX_INT || info->t_eat > MAX_INT 
		|| info->t_sleep > MAX_INT || info->must_eat < 0)
		return (0);
	return (1);
}
