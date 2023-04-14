/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/14 19:36:06 by yongmipa         ###   ########seoul.kr  */
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

void	*cherhakjas_routine(void *cherhakjas)
{
	// 포크가 있으면 집는다.
	if (!pthread_mutex_lock(cherhakjas)) // 성공
	{

	}
	while (!pthread_mutex_lock)
		;
	
	// 먹는다.
	// 포크를 내려 놓는다. 
	// 생각 한다. 
}

void	eating(t_philo *philo)
{
	
}

void	sleeping(t_philo *philo)
{

}

void	thinking(t_philo *philo)
{
	
}
