/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongmipa <yongmipa@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:21:34 by yongmipa          #+#    #+#             */
/*   Updated: 2023/04/12 20:53:30 by yongmipa         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*make_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	*forks;

	i = -1;
	forks = (pthread_mutex_t *)malloc(info->num * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	while (++i < info->num)
		pthread_mutex_init(&forks[i], NULL);
	return (forks);
}

t_philo	*make_cherhakja(t_info *info, pthread_mutex_t *forks)
{
	t_philo	*cherhakja;
	int		i;

	i = -1;
	cherhakja = (t_philo *)malloc(info->num * sizeof(t_philo));
	if (!cherhakja)
		return (NULL);
	while (++i < info->num)
	{
		cherhakja[i].amount_eat = 0;
		cherhakja[i].last_eating = 0;
		cherhakja[i].p_index = i;
		cherhakja[i].info = info;
		cherhakja[i].lfork = &forks[i];
		cherhakja[i].rfork = &forks[(info->num + i - 1) % info->num];
	}
	return (cherhakja);
}

t_philo	*set_cherhakjas(t_info *info)
{
	t_philo	*cherhakjas;

	info->forks = make_forks(info);
	if (!info->forks)
	{
		ft_free(info);
		return (NULL);
	}
	cherhakjas = make_cherhakja(info, info->forks);
	if (!cherhakjas)
	{
		ft_free(info);
		return (NULL);
	}
	return (cherhakjas);
}

// pthread_t	*sit_down_cherhak_man(t_philo *cherhakjas, t_info *info)
// {
// 	pthread_t	*table;
// 	int			i;

// 	table = (pthread_t *)malloc(sizeof(pthread_t) * info->num);
// 	if (!table)
// 	{
// 		ft_free(&info);
// 		return (NULL);
// 	}
// 	i = -1;
// 	while (++i < info->num)
// 	{
// 		table[i] = pthread_create(&table[i], NULL, cherhakjas_routine, &cherhakjas[i]);
// 	}
	
// 	return (table);
// }

//제가 생각한 필로소퍼 구조입니다 

// void	suhwpark(t_info *info, t_philo *philos, pthread_t *table)
// {
// 	int	i;

// 	i = -1;
// 	info->time = get_times(); // 이거는 만들어봐여
// 	while (++i < info->num)
// 	{
// 		pthread_mutex_lock(&(info->philo_mutex));
// 		philos[i].last_eating = info->start_time;
// 		pthread_mutex_unlock(&(info->philo_mutex));
// 		if (!(i % 2))
// 			pthread_create(&table[i], 0, cherhakjas_routine, &philos[i]);
// 	}
// 	// 여기서 usleep을 해야할듯
// 	usleep();
// 	i = -1;
// 	while (++i < info->num)
// 	{
// 		if (i % 2)
// 			pthread_create(&table[i], 0, cherhakjas_routine, &philos[i]);
// 	}
// 	//이제여기서 철학자들 모니터링 하면 될듯!
// }

void	only_one_cherhakja(t_philo *cherhakjas, t_info *info)
{
	int	i;

	i = -1;
	usleep(800);
	print_msg(relative_time() - info->start_time, cherhakjas, "has taken a fork");
	while (++i * 100 < info->t_die)
		usleep(1000);
	print_msg(relative_time() - info->start_time, cherhakjas, "died");
	pthread_mutex_destroy(cherhakjas[0].lfork);
	pthread_mutex_destroy(cherhakjas[0].rfork);
}

int	main(int ac, char **av)
{
	t_info		info;
	t_philo		*cherhakjas;
	pthread_t	*phillo_in_table;

	if (ac < 5 || ac > 6)
		return (-1);
	if (!validate_info(ac, av, &info))
		return (-1);
	cherhakjas = set_cherhakjas(&info);
	if (!cherhakjas)
		return (-1);
	if (info.num == 1)
	{
		only_one_cherhakja(cherhakjas, &info);
		pthread_mutex_destroy(&info.philo_mutex);
		pthread_mutex_destroy(&info.info_mutex);
		return (-1);
	}
	phillo_in_table = (pthread_t *)malloc(sizeof(pthread_t) * info.num);
	if (!phillo_in_table)
		return (-1);
	// suhwpark(&info, cherhakjas, phillo_in_table);
	return (0);
}
