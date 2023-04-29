/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:52 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/29 20:42:07 by yongmipa         ###   ########seoul.kr  */
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

static int	*make_forks_bundle(t_info *info)
{
	int	*forks_bundle;
	int	i;

	i = -1;
	forks_bundle = (int *)malloc(info->num * sizeof(int));
	if (!forks_bundle)
		return (NULL);
	while (++i < info->num)
		forks_bundle[i] = 1;
	return (forks_bundle);
}

t_philo	*sit_philo(t_info *info, pthread_mutex_t *forks, int *forks_bundle)
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
		philo[i].left = &forks_bundle[i];
		philo[i].right = &forks_bundle[(info->num + i - 1) % info->num];
	}
	return (philo);
}

t_philo	*set_philo(t_info *info)
{
	t_philo	*philo;

	info->forks = make_forks(info);
	if (!info->forks)
		return (NULL);
	info->forks_bundle = make_forks_bundle(info);
	if (!info->forks_bundle)
		return (NULL);
	philo = sit_philo(info, info->forks, info->forks_bundle);
	if (!philo)
	{
		free(info->forks);
		return (NULL);
	}
	return (philo);
}

void	input_philo(t_info *info, t_philo *philos, pthread_t *table)
{
	int	i;

	i = -1;
	info->start_time = relative_time();
	while (++i < info->num)
	{
		pthread_mutex_lock(&(info->philo_mutex));
		philos[i].last_eating = info->start_time;
		pthread_mutex_unlock(&(info->philo_mutex));
		if (!(i % 2))
			pthread_create(&table[i], 0, (void *)routine, &philos[i]);
	}
	// usleep((info->num / 2) * 1000);
	usleep(500);
	i = -1;
	while (++i < info->num)
		if (i % 2)
			pthread_create(&table[i], 0, (void *)routine_2, &philos[i]);
	monitor(philos, table);
}
