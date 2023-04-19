/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/19 22:14:49 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_msg(philo->info->start_time, philo, PICK);
	pthread_mutex_lock(philo->rfork);
	print_msg(philo->info->start_time, philo, PICK);
	print_msg(philo->info->start_time, philo, EATING);
	pthread_mutex_lock(&(philo->info)->philo_mutex);
	philo->amount_eat += 1;
	if (philo->info->must_eat == philo->amount_eat)
	{
		philo->info->end_flag = 2;
		pthread_mutex_unlock(&(philo->info)->philo_mutex);
		return ;
	}
	philo->last_eating = relative_time();
	pthread_mutex_unlock(&(philo->info)->philo_mutex);
	ft_usleep(relative_time(), philo->info->t_eat);
	//먹는 순간 업데이트를 하고 시간을 흘려보내는 방식으로 변경
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	print_msg(philo->info->start_time, philo, SLEEPING);
	ft_usleep(relative_time(), philo->info->t_sleep);
	print_msg(philo->info->start_time, philo, THINKING);
}

int	is_dead(t_info *info)
{
	pthread_mutex_lock(&(info->philo_print));
	if (info->end_flag)
	{
		pthread_mutex_unlock(&(info->philo_print));
		return (1);
	}
	pthread_mutex_unlock(&(info->philo_print));
	return (0);
}

void	*routine(t_philo *philo)
{
	while (!is_dead(philo->info))
	{
		eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
