/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:50:28 by sohyupar          #+#    #+#             */
/*   Updated: 2023/04/19 21:13:28 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

t_philo	*sit_philo(t_info *info, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)malloc(info->num * sizeof(t_philo));
	if (!philo)
		return (NULL);
	while (++i < info->num)
	{
		philo[i].amount_eat = 0;
		philo[i].last_eating = 0;
		philo[i].p_index = i;
		philo[i].info = info;
		philo[i].lfork = &forks[i];
		philo[i].rfork = &forks[(info->num + i - 1) % info->num];
	}
	return (philo);
}

t_philo	*set_philo(t_info *info)
{
	t_philo	*philo;

	info->forks = make_forks(info);
	if (!info->forks)
	{
		ft_free(info, NULL);
		return (NULL);
	}
	philo = sit_philo(info, info->forks);
	if (!philo)
	{
		ft_free(info, NULL);
		return (NULL);
	}
	return (philo);
}

void	input_philo(t_info *info, t_philo *philos, pthread_t *table)
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
	usleep(50);
	i = -1;
	while (++i < info->num)
	{
		if (i % 2)
			pthread_create(&table[i], 0, (void *)routine, &philos[i]);
	}
	monitor(philos, table);
}
