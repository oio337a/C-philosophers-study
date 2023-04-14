/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/14 18:26:06 by yongmipa         ###   ########seoul.kr  */
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
	printf("%llu	%d	%s\n", seconds, philo->p_index, msg);
}
