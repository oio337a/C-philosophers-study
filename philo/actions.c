/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/14 22:27:55 by yongmipa         ###   ########seoul.kr  */
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
	MS	i;

	i = 0;
	print_msg(relative_time() - philo->info->start_time, philo, PICK);
	while (i < philo->info->t_eat)
	{
		if (!pthread_mutex_lock(&(philo->info)->info_mutex))
		{
			usleep(1000);
			print_msg(relative_time() - philo->info->start_time, philo, EATING);
			pthread_mutex_unlock(&(philo->info)->info_mutex);
		}
		else
		{
			print_msg(relative_time() - philo->info->start_time, philo, DIED);
			return ;
		}
		i++;
	}
	pthread_mutex_unlock(philo->lfork);
	pthread_mutex_unlock(philo->rfork);
	philo->last_eating = relative_time();
	print_msg(relative_time() - philo->info->start_time, philo, DIED);
	usleep(1000);
}

// static void	sleeping(t_philo *philo)
// {

// }

// static void	thinking(t_philo *philo)
// {
// }
void	*cherhakjas_routine(t_philo *cherhakjas)
{
	// 포크가 있으면 집는다.
	while (pthread_mutex_lock(cherhakjas->lfork) || pthread_mutex_lock(cherhakjas->rfork))
		;
	if (relative_time() - cherhakjas->last_eating > cherhakjas->info->t_die)
	{
		pthread_mutex_lock(&(cherhakjas->info)->info_mutex);
		return (NULL);
	}
	// 포크 2개 다잡음
	// 먹는다.
	eating(cherhakjas);
	// 포크를 내려 놓는다.
	// 생각 한다.
	
	if (!(relative_time() - cherhakjas->last_eating > cherhakjas->info->t_die))
		cherhakjas_routine(cherhakjas);
	return (NULL);
}
