/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/19 17:01:14 by sohyupar         ###   ########.fr       */
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
		pthread_mutex_destroy(&info->philo_print);
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

	pthread_mutex_lock(&(philo->info)->philo_print);
	time = relative_time() - seconds;
	if (philo->info->end_flag)
	{
		pthread_mutex_unlock(&(philo->info)->philo_print);
		return ;
	}
	printf("%llu %d %s\n", time, philo->p_index, msg);
	// printf("\033[0m");
	pthread_mutex_unlock(&(philo->info)->philo_print);
}

MS	get_time(MS start)
{
	MS	now;

	now = relative_time();
	return (now - start);
}

void	ft_usleep(MS time, MS finish)
{
	while (get_time(time) < finish)
		usleep(100);
}
