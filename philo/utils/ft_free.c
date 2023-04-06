/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:15:17 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/06 18:17:43 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*ft_free(t_info *info)
{
	pthread_mutex_destroy(info->info_mutex);
	pthread_mutex_destroy(info->philo_mutex);
	return (NULL);
}
