/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/02 15:13:53 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	in_monitor(t_philo *philo)
{
	int	i;
	MS	time;

	i = -1;
	while (++i < philo[0].info->num)
	{
		if (is_dead(philo[i].info))
			return (1);
		pthread_mutex_lock(&philo[i].info->philo_mutex);
		time = philo[i].last_eating;
		pthread_mutex_unlock(&philo[i].info->philo_mutex);
		if (relative_time() - time >= philo->info->t_die)
		{
			pthread_mutex_lock(&philo[i].info->philo_check_dead);
			philo->info->end_flag = 1;
			pthread_mutex_unlock(&philo[i].info->philo_check_dead);
			pthread_mutex_lock(&philo[i].info->philo_print);
			printf("%llu	%d %s\n",
				relative_time() - philo[i].info->start_time,
				philo[i].p_index + 1, DIED);
			pthread_mutex_unlock(&philo[i].info->philo_print);
			return (1);
		}
	}
	return (0);
}

void	monitor(t_philo *philo, pthread_t *table)
{
	int	i;

	i = -1;
	while (1)
	{
		if (in_monitor(philo))
			break ;
	}
	while (++i < philo[0].info->num)
		pthread_join(table[i], NULL);
}

static int	one_philo(t_philo *philo, t_info *info)
{
	print_msg(info->start_time, philo, PICK);
	ft_usleep(info->start_time, info->t_die, philo);
	print_msg(info->start_time, philo, DIED);
	ft_free(info, philo, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_philo		*philo;
	pthread_t	*phillo_in_table;

	if (ac < 5 || ac > 6)
		return (-1);
	if (!validate_info(ac, av, &info))
		return (-1);
	philo = set_philo(&info);
	if (!philo)
		return (-1);
	if (info.num == 1)
		return (one_philo(philo, &info));
	phillo_in_table = (pthread_t *)malloc(sizeof(pthread_t) * info.num);
	if (!phillo_in_table)
		return (-1);
	input_philo(&info, philo, phillo_in_table);
	ft_free(&info, philo, phillo_in_table);
	return (0);
}
