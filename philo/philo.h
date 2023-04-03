/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:24:46 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/03 17:34:59 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MS	unsigned long long
# define FORK		0
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4

# define MAX_INT 2147483647
# define MIN_INT -2147483648

typedef struct s_info
{
	int	num;
	MS	t_die;
	MS	t_eat;
	MS	t_sleep;
	int	must_eat;
}	t_info;

typedef struct s_philo
{
	int				p_index;
	MS				last_eating;
	int				amount_eat;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_info			*info;
}	t_philo;

//utils
size_t	relative_time(size_t time_start);
int		validate_info(int ac, char **av, t_info *info);
#endif