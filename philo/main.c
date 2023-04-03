/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:21:34 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/03 17:24:47 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*make_cherhakja(t_info *info)
{
	t_philo *cherhakja;

	info->
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*cherhakja;

	if (ac < 5 || ac > 6)
		return (-1);
	if (!validate_info(ac, av, &info))
		return (-1);
	cherhakja = make_cherhakja(&info);
	return (0);
}

