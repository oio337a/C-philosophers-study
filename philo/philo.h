/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:31:31 by yongmipa          #+#    #+#             */
/*   Updated: 2023/05/01 22:17:17 by yongmipa         ###   ########seoul.kr  */
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

# define MS			unsigned long long
# define MAX_INT	2147483647
# define MIN_INT	-2147483648

# define PICK		"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

typedef struct s_info
{
	int				num;
	MS				t_die;
	MS				t_eat;
	MS				t_sleep;
	int				must_eat;
	MS				start_time;
	int				end_flag;
	int				meals;
	pthread_mutex_t	philo_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	philo_print;
	pthread_mutex_t	philo_check_dead;
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

MS				relative_time(void);
MS				get_time(MS start);
int				validate_info(int ac, char **av, t_info *info);
int				is_dead(t_info *info);
void			ft_free(t_info *info, t_philo *philo, pthread_t *table);
void			*routine(t_philo *philo);
void			print_msg(MS seconds, t_philo *philo, char *msg);
void			ft_usleep(MS time, MS finish, t_philo *philo);
void			input_philo(t_info *info, t_philo *philos, pthread_t *table);
void			monitor(t_philo *philo, pthread_t *table);
t_philo			*sit_philo(t_info *info, pthread_mutex_t *forks);
t_philo			*set_philo(t_info *info);
pthread_mutex_t	*make_forks(t_info *info);
#endif