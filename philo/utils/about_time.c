/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/10 18:23:39 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	relative_time(size_t time_start)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - time_start);
}
// 이거 블로그에서 본건데여 time_start - 현재 시간을 뺀거에여 얼마나 걸렸나 반환.