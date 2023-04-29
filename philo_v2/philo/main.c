/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:07 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/27 16:21:59 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(t_philo *philo, t_info *info)
{
	print_msg(info->start_time, philo, PICK);
	ft_usleep(info->start_time, info->t_die);
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
