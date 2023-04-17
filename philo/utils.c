/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/17 21:54:20 by yongmipa         ###   ########seoul.kr  */
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

void	ft_usleep(MS time)
{
	usleep(1000 * time);
}
