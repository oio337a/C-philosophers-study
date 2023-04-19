/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sohyupar <sohyupar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:24:46 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/19 18:03:13 by sohyupar         ###   ########.fr       */
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
# define FORK		0
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4

# define MAX_INT	2147483647
# define MIN_INT	-2147483648

// # define PICK		"\033[38:5:225m	🥄 has taken a fork"
// # define EATING		"\033[38:5:51m	🍝 is eating"
// # define SLEEPING	"\033[38:5:208m	🌜 is sleeping"
// # define THINKING	"\033[38:5:252m	🧐 is thinking"
// # define DIED		"\033[38:5:196m	🧟‍♂️ died"

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
	int				end_flag;// 철학자 죽었을 때 0으로 만들어서 출력 불가
	pthread_mutex_t	philo_mutex;  // 철학자들 감시
	pthread_mutex_t	*forks; // 포크들
	pthread_mutex_t	philo_print;
}	t_info;

typedef struct s_philo
{
	int				p_index;
	MS				last_eating;
	int				amount_eat;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	t_info	*info;
}	t_philo;

// size_t	relative_time(size_t time_start);
MS		relative_time(void);
int		validate_info(int ac, char **av, t_info *info);
void	*ft_free(t_info *info, t_philo *philo);
void	*routine(t_philo *philo);
void	print_msg(MS seconds, t_philo *philo, char *msg);
void	ft_usleep(MS time, MS finish);
MS		get_time(MS start);
int		is_dead(t_info *info);
void	free_philo(t_philo *philo);
pthread_mutex_t	*make_forks(t_info *info);
t_philo	*sit_philo(t_info *info, pthread_mutex_t *forks);
t_philo	*set_philo(t_info *info);
void	input_philo(t_info *info, t_philo *philos, pthread_t *table);
void	monitor(t_philo *philo, pthread_t *table);
#endif