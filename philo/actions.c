/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:01 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/10 18:14:36 by yongmipa         ###   ########seoul.kr  */
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
	/*
		timestamp_in_ms X has taken a fork
		timestamp_in_ms X is eating
		timestamp_in_ms X is sleeping
		timestamp_in_ms X is thinking
		timestamp_in_ms X died
	*/
	// 생성 됬으니 뮤택스 끌까여? 1명 생성되면? 왜냐면 출력을 한명씩 해명씩 해야하는거 잖아여.
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
