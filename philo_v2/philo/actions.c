/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:23 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/29 20:46:14 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_number_of_meals(t_philo *philo)
{
	if (!philo->info->must_eat)
		return ;
	pthread_mutex_lock(&philo->info->philo_mutex);
	++(philo->amount_eat);
	pthread_mutex_unlock(&philo->info->philo_mutex);
	if (philo->amount_eat == philo->info->must_eat)
	{
		pthread_mutex_lock(&philo->info->philo_mutex);
		++(philo->info->meals);
		pthread_mutex_unlock(&philo->info->philo_mutex);
		if (philo->info->meals == philo->info->num)
		{
			pthread_mutex_lock(&philo->info->philo_check_dead);
			philo->info->end_flag = 2;
			pthread_mutex_unlock(&philo->info->philo_check_dead);
		}
	}
	return ;
}

static void	eating(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		if (*philo->left)
		{
			*philo->left = 0;
			pthread_mutex_unlock(philo->lfork);
			break ;
		}
		pthread_mutex_unlock(philo->lfork);
	}
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, PICK);
	while (1)
	{
		pthread_mutex_lock(philo->rfork);
		if (*philo->right)
		{
			*philo->right = 0;
			pthread_mutex_unlock(philo->rfork);
			break ;
		}
		pthread_mutex_unlock(philo->rfork);
	}
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, PICK);
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, EATING);
	pthread_mutex_lock(&philo->info->philo_update_time);
	philo->last_eating = relative_time();
	pthread_mutex_unlock(&philo->info->philo_update_time);
	check_number_of_meals(philo);
	ft_usleep(relative_time(), philo->info->t_eat, philo);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	*(philo->left) = 1;
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_lock(philo->rfork);
	*(philo->right) = 1;
	pthread_mutex_unlock(philo->rfork);
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, SLEEPING);
	ft_usleep(relative_time(), philo->info->t_sleep, philo);
	if (is_dead(philo->info))
		return ;
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

static void	eating_2(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->rfork);
		if (*philo->right)
		{
			*philo->right = 0;
			pthread_mutex_unlock(philo->rfork);
			break ;
		}
		pthread_mutex_unlock(philo->rfork);
	}
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, PICK);
	while (1)
	{
		pthread_mutex_lock(philo->lfork);
		if (*philo->left)
		{
			*philo->left = 0;
			pthread_mutex_unlock(philo->lfork);
			break ;
		}
		pthread_mutex_unlock(philo->lfork);
	}
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, PICK);
	if (is_dead(philo->info))
		return ;
	print_msg(philo->info->start_time, philo, EATING);
	pthread_mutex_lock(&philo->info->philo_update_time);
	philo->last_eating = relative_time();
	pthread_mutex_unlock(&philo->info->philo_update_time);
	check_number_of_meals(philo);
	ft_usleep(relative_time(), philo->info->t_eat, philo);
}

void	*routine_2(t_philo *philo)
{
	while (!is_dead(philo->info))
	{
		eating_2(philo);
		sleeping(philo);
	}
	return (NULL);
}
