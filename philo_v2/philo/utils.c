/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:30:59 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/27 20:35:54 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

MS	relative_time(void)
{
	struct timeval	current;

	gettimeofday(&current, 0);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

void	ft_free(t_info *info, t_philo *philo, pthread_t *table)
{
	int	i;

	i = -1;
	while (++i < info->num)
		pthread_mutex_destroy(philo[i].lfork);
	pthread_mutex_destroy(&(info->philo_mutex));
	pthread_mutex_destroy(&(info->philo_print));
	pthread_mutex_destroy(&(info->philo_check_dead));
	pthread_mutex_destroy(&(info->philo_update_time));
	free(info->forks);
	free(philo);
	if (table)
		free(table);
}

void	print_msg(MS seconds, t_philo *philo, char *msg)
{
	MS	time;

	pthread_mutex_lock(&philo->info->philo_check_dead);
	if (philo->info->end_flag)
	{
		pthread_mutex_unlock(&philo->info->philo_check_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->info->philo_check_dead);
	pthread_mutex_lock(&philo->info->philo_print);
	time = relative_time() - seconds;
	printf("%llu	%d %s\n", time, philo->p_index, msg);
	pthread_mutex_unlock(&philo->info->philo_print);
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
		usleep(200);
}
