/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/18 18:27:48 by sohyupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

MS	relative_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	*ft_free(t_info *info, t_philo *cherhakjas)
{
	if (!cherhakjas)
	{
		pthread_mutex_destroy(&info->info_mutex);
		pthread_mutex_destroy(&info->philo_mutex);
	}
	if (!info)
	{
		while (info->num--)
		{
			pthread_mutex_destroy(cherhakjas[info->num].lfork);
			pthread_mutex_destroy(cherhakjas[info->num].rfork);
		}
	}
	return (NULL);
}

void	print_msg(MS seconds, t_philo *philo, char *msg)
{
	MS	time;

	time = relative_time() - seconds;
	pthread_mutex_lock(&(philo->info)->philo_mutex);
	printf("%llu	%d	%s\n", time, philo->p_index, msg);
	pthread_mutex_unlock(&(philo->info)->philo_mutex);
	printf("\033[0m");
}

/*
이런 식으로 한번에 통째로 1ms씩 시간을 보내게 되면 여러 곳에서 서로 쓰려 할 때 밀리는 현상이 일어남
방지하는 방법은 시간을 쪼갠 다음에 보내야된대여
while (실제 지난 시간 <= 보내야 하는 시간)
	usleep(100);
이렇게 한다는데

기능별 mutex가 한번에 한 동작만 판별하도록 별개로 있었으면 함...
지금 떠오르는건 last_eat, print, forks, philo 정도???
변수명 넘나 헷갈려서 통일햇어요
*/
void	ft_usleep(MS time)
{
	usleep(1000 * time);
}

void	ft_usleep2(MS time, MS finish)
{
	while (time <= finish)
		usleep(100);
}
