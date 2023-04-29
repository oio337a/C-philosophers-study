/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:20:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/27 20:37:46 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_info *info)
{

	pthread_mutex_lock(&(info->philo_check_dead));
	if (info->end_flag)
	{
		pthread_mutex_unlock(&(info->philo_check_dead));
		return (1);
	}
	pthread_mutex_unlock(&(info->philo_check_dead));
	return (0);
	
}

static int	in_monitor(t_philo *philo)
{
	int	i;
	MS	time;

	i = -1;
	while (++i < philo[0].info->num)
	{
		if (is_dead(philo[i].info))
			return (1);
		pthread_mutex_lock(&philo[i].info->philo_mutex);
		time = philo[i].last_eating;
		pthread_mutex_unlock(&philo[i].info->philo_mutex);
		if (relative_time() - time >= philo->info->t_die)
		{
			print_msg(philo[i].info->start_time, &philo[i], DIED);
			pthread_mutex_lock(&philo[i].info->philo_check_dead);
			philo->info->end_flag = 1;
			pthread_mutex_unlock(&philo[i].info->philo_check_dead);
			return (1);
		}
	}
	return (0);
}

void	monitor(t_philo *philo, pthread_t *table)
{
	int	i;

	i = -1;
	while (1)
	{
		if (in_monitor(philo))
			break ;
		usleep(600);
	}
	while (++i < philo[0].info->num)
		pthread_join(table[i], NULL);
}
