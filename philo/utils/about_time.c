/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   about_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:14:09 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/12 18:41:18 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

size_t	relative_time(size_t time_start)
{
	struct timeval	current;

	// gettimeofday(&current, NULL);
	// printf("1. %d\n", current.tv_usec);
	// // usleep(1000);
	gettimeofday(&current, 0);
	printf("1. %zd\n", current.tv_usec);
	printf("2. %zd\n", time_start);
	
	return (current.tv_sec * 1000 * 1000 + current.tv_usec - time_start);
	// return ((current.tv_sec - time_start) / (1000 * 1000));
	// return ((current.tv_usec - time_start) / (1000 * 1000));
	// return ((time_start - current.tv_usec) / (1000 * 1000));

}
// 이거 블로그에서 본건데여 time_start - 현재 시간을 뺀거에여 얼마나 걸렸나 반환.