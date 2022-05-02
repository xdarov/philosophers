/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:23:55 by pcorina           #+#    #+#             */
/*   Updated: 2022/03/09 21:01:30 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_var(void *link)
{
	t_philo	*philo;
	int		buf;

	philo = (t_philo *)link;
	philo->p = philo->m1 + 1;
	if (philo->m1 % 2)
	{
		buf = philo->m2;
		philo->m2 = philo->m1;
		philo->m1 = buf;
	}
	return (philo);
}

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + time.tv_usec / 1000);
	usleep(100);
}

void	output(t_philo *philo, char *str, long time)
{
	pthread_mutex_lock(&philo->mut[philo->num_philo + 1]);
	if (!*philo->death)
		printf("%ld %d philo %s\n", philo->t + time, philo->p, str);
	pthread_mutex_unlock(&philo->mut[philo->num_philo + 1]);
}

int	check_death(t_philo *philo, long time)
{
	if (time >= philo->die)
	{
		if (*philo->death == 1)
			return (1);
		*philo->death = 1;
		usleep(10);
		printf("%ld %d philo died\n", time + philo->t, philo->p);
		return (1);
	}
	else
		return (0);
}

int	check_eat_num(int *eat_num)
{
	if (*eat_num == -1)
		return (1);
	else if (*eat_num == 0)
		return (0);
	else
		return (--(*eat_num) + 1);
}
