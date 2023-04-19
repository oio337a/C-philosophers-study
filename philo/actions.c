/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/19 16:31:07 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	여기서 걍 같이 print 해주는거 어때여
	thinking - 특별한 거 없이 과제에서 요구한 거에 맞춰서 출력 - 밥먹거나 자는 시간 빼고 얘로 넘어감
	pickup porks - 양쪽에 있는 공유자원인 포크를 드는 행위
	eating - 밥을 먹었으니 죽을 시간을 갱신, 먹은 횟수 체크, 포크를 내려놓는 행위
	sleep - 잠
*/

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	print_msg(philo->info->start_time, philo, PICK);
	pthread_mutex_lock(philo->rfork);
	print_msg(philo->info->start_time, philo, PICK);
	print_msg(philo->info->start_time, philo, EATING);
	pthread_mutex_lock(&(philo->info)->philo_mutex);
	philo->last_eating = relative_time();
	pthread_mutex_unlock(&(philo->info)->philo_mutex);
	ft_usleep(relative_time(), philo->info->t_eat);
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
	if (info->end_flag == 1)
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
