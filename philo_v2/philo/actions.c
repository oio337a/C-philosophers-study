/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:23 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:53 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_number_of_meals(t_philo *philo)
{
	if (!philo->info->must_eat)
		return ;
	++(philo->amount_eat);
	if (philo->amount_eat == philo->info->must_eat)
	{
		++(philo->info->meals);
		if (philo->info->meals == philo->info->num)
			philo->info->end_flag = 2;
	}
	return ;
}

static void	eating(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		if (philo->left)
		{
			*philo->left = 0;
			pthread_mutex_unlock(philo->lfork);
			break ;
		}
		pthread_mutex_unlock(philo->lfork);
	}
	print_msg(philo->info->start_time, philo, PICK);
	while (1)
	{
		pthread_mutex_lock(philo->rfork);
		if (philo->right)
		{
			*philo->right = 0;
			pthread_mutex_unlock(philo->rfork);
			break ;
		}
		pthread_mutex_unlock(philo->rfork);
	}
	print_msg(philo->info->start_time, philo, PICK);
	print_msg(philo->info->start_time, philo, EATING);
	pthread_mutex_lock(&philo->info->philo_update_time);
	philo->last_eating = relative_time();
	pthread_mutex_unlock(&philo->info->philo_update_time);
	pthread_mutex_lock(&philo->info->philo_mutex);
	check_number_of_meals(philo);
	pthread_mutex_unlock(&philo->info->philo_mutex);
	//곳곳에 is_dead 추가하기
	ft_usleep(relative_time(), philo->info->t_eat);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	*(philo->left) = 1;
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	*(philo->right) = 1;
	pthread_mutex_unlock(philo->rfork);
	//곳곳에 is_dead 추가하기
	print_msg(philo->info->start_time, philo, SLEEPING);
	//곳곳에 is_dead 추가하기
	ft_usleep(relative_time(), philo->info->t_sleep);
	print_msg(philo->info->start_time, philo, THINKING);
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
