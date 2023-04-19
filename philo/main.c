/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:21:34 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/19 16:51:38 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	in_monitor(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->info->num)
	{
		pthread_mutex_lock(&(philo->info)->philo_mutex);
		if (relative_time() - (&philo[i])[0].last_eating >= philo->info->t_die)
		{
			print_msg(philo->info->start_time, &philo[i], DIED);
			philo->info->end_flag = 1;
			pthread_mutex_unlock(&(philo->info)->philo_mutex);
			return (1);
		}
		pthread_mutex_unlock(&(philo->info)->philo_mutex);
	}
	return (0);
}

static void	monitor(t_philo *philo, pthread_t *table)
{
	int	i;

	i = -1;
	while (1)
		if (in_monitor(philo))
			break ;
	while (++i < philo[0].info->num)
	{
		if (philo->info->end_flag == 1)
		{
			pthread_detach(table[i]);
			i++;
		}
		pthread_join(table[i], NULL);
	}
}

/*


		while (1)
	{
		pthread_mutex_lock(&(philo->info)->philo_mutex);
		if (relative_time() - philo->last_eating >= philo->info->t_die)
		{
			print_msg(philo->info->start_time, philo, DIED);
			philo->info->end_flag = 1;
			pthread_mutex_unlock(&(philo->info)->philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&(philo->info)->philo_mutex);
	}
*/

pthread_mutex_t	*make_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = (pthread_mutex_t *)malloc(info->num * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	while (++i < info->num)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

t_philo	*make_cherhakja(t_info *info, pthread_mutex_t *forks)
{
	t_philo	*cherhakja;
	int		i;

	i = -1;
	cherhakja = (t_philo *)malloc(info->num * sizeof(t_philo));
	if (!cherhakja)
		return (NULL);
	while (++i < info->num)
	{
		cherhakja[i].amount_eat = 0;
		cherhakja[i].last_eating = 0;
		cherhakja[i].p_index = i;
		cherhakja[i].info = info;
		cherhakja[i].lfork = &forks[i];
		cherhakja[i].rfork = &forks[(info->num + i - 1) % info->num];
	}
	return (cherhakja);
}

t_philo	*set_cherhakjas(t_info *info)
{
	t_philo	*cherhakjas;

	info->forks = make_forks(info);
	if (!info->forks)
	{
		ft_free(info, NULL);
		return (NULL);
	}
	cherhakjas = make_cherhakja(info, info->forks);
	if (!cherhakjas)
	{
		ft_free(info, NULL);
		return (NULL);
	}
	return (cherhakjas);
}

//제가 생각한 필로소퍼 구조입니다 

void	suhwpark(t_info *info, t_philo *philos, pthread_t *table) // 5 800 200 
{
	int	i;

	i = -1;
	while (++i < info->num)
	{
		pthread_mutex_lock(&(info->philo_mutex));
		philos[i].last_eating = info->start_time;
		pthread_mutex_unlock(&(info->philo_mutex));
		if (!(i % 2))
			pthread_create(&table[i], 0, (void *)routine, &philos[i]);
	}
	usleep(100);
	i = -1;
	while (++i < info->num)
	{
		if (i % 2)
			pthread_create(&table[i], 0, (void *)routine, &philos[i]);
	}
	//이제여기서 철학자들 모니터링 하면 될듯!
	monitor(philos, table);
}

static int	only_one_cherhakja(t_philo *cherhakjas, t_info *info)
{
	print_msg(info->start_time, cherhakjas, PICK);
	usleep(1000 * info->t_die);
	print_msg(info->start_time, cherhakjas, DIED);
	ft_free(info, cherhakjas);
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_philo		*cherhakjas;
	pthread_t	*phillo_in_table;

	if (ac < 5 || ac > 6)
		return (-1);
	if (!validate_info(ac, av, &info))
		return (-1);
	cherhakjas = set_cherhakjas(&info);
	if (!cherhakjas)
		return (-1);
	if (info.num == 1)
		return (only_one_cherhakja(cherhakjas, &info));
	phillo_in_table = (pthread_t *)malloc(sizeof(pthread_t) * info.num);
	if (!phillo_in_table)
		return (-1);
	suhwpark(&info, cherhakjas, phillo_in_table);
	return (0);
}
