#include "philo.h"

int	philo_init(void)
{
	int			i;
	pthread_t	philo;

	i = -1;
	while (++i < 5)
	{
		if (pthread_create(&philo, NULL, &routine, (void *)&common) != 0)
			return (1);
		if (pthread_detach(philo) != 0)
			return (1);
	}
}

pthread_mutex_t	*init_forks()
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	if (!(forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 5)))
		return (NULL);
	while (++i < 5)
	{
		if (pthread_mutex_init(&forks[i], NULL) < 0)
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

typedef struct s_test
{
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
}	t_philo2;


void	pick_up(t_philo2 *philo)
{
	pthread_mutex_lock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
}

void	sleep_philo(t_philo2 *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);

}

t_philo2	*input_philo()
{
	t_philo2	*philo;
	pthread_mutex_t	*forks;
	int	i;

	i = 0;
	if (!(philo = (t_philo2 *)malloc(sizeof(t_philo2) * 5)))
		return (NULL);
	if (!(forks = init_forks()))
		return (NULL);
	while (i < 5)
	{
		philo[i].rfork = &forks[(i + 1) % 5];
		philo[i].lfork = &forks[i];
		i++;
	}
	return (philo);
}