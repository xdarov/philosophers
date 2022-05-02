/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:23:55 by pcorina           #+#    #+#             */
/*   Updated: 2022/04/27 16:15:15 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	output(t_philo *philo, char *str, long time)
{
	sem_wait(philo->out);
	printf("%ld %d philo %s\n", philo->t + time, philo->p, str);
	sem_post(philo->out);
}

int	check_death(t_philo *philo, long time)
{
	if (time >= philo->die)
	{
		sem_wait(philo->out);
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
