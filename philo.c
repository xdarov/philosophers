/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:01:44 by pcorina           #+#    #+#             */
/*   Updated: 2022/03/11 16:32:20 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_philo *philo, char **argv, int argc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]) || \
			(ft_atoi(argv[i]) <= 0 && argv[i][0] != '0'))
				return (1);
	}
	philo->num_philo = ft_atoi(argv[1]);
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	philo->mut = malloc(sizeof(pthread_mutex_t) * (philo->num_philo + 2));
	philo->thread = malloc(sizeof(pthread_t *) * philo->num_philo);
	if (!philo->mut || !philo->thread)
		return (-1);
	i = -1;
	while (++i < philo->num_philo + 2)
		pthread_mutex_init(&philo->mut[i], NULL);
	return (0);
}

void	creating_streams(t_philo *philo)
{
	int	i;

	if (philo->num_philo > 0)
	{
		i = -1;
		while (++i < philo->num_philo)
		{
			pthread_mutex_lock(&philo->mut[philo->num_philo]);
			philo->m1 = i;
			if (!i)
				philo->m2 = philo->num_philo - 1;
			else
				philo->m2 = i - 1;
			pthread_create(&philo->thread[i], NULL, philo_life, philo);
		}
		while (!*philo->death)
			usleep(1000);
		usleep(1000);
	}
}

int	eat_ph(t_philo *philo, long time)
{
	pthread_mutex_lock(&philo->mut[philo->m1]);
	output(philo, "took 1 fork", time_now() - time);
	pthread_mutex_lock(&philo->mut[philo->m2]);
	output(philo, "took 2 fork", time_now() - time);
	output(philo, "eat", time_now() - time);
	philo->start_eat = time_now();
	while (philo->eat + philo->start_eat > time_now())
	{
		usleep(100);
		if (check_death(philo, time_now() - philo->start_eat))
			return (1);
	}
	pthread_mutex_unlock(&philo->mut[philo->m1]);
	pthread_mutex_unlock(&philo->mut[philo->m2]);
	if (!philo->eat_num)
		return (1);
	return (0);
}

int	sl_th_ph(t_philo *philo, long time)
{
	int	start_sleep;
	int	start_thinks;

	output(philo, "sleep", time_now() - time);
	start_sleep = time_now() - time;
	while (start_sleep + philo->sleep + time > time_now())
	{
		usleep(100);
		if (check_death(philo, time_now() - philo->start_eat))
			return (1);
	}
	start_thinks = time_now() - time;
	output(philo, "thinks", time_now() - time);
	while (philo->eat * 2 + philo->start_eat > time_now())
	{
		usleep(100);
		if (check_death(philo, time_now() - philo->start_eat))
			return (1);
	}
	return (0);
}

void	*philo_life(void *link)
{
	t_philo		philo;
	long		time;

	philo = *init_var(link);
	pthread_mutex_unlock(&philo.mut[philo.num_philo]);
	if (check_death(&philo, 0))
		return (NULL);
	if (philo.num_philo != 1)
	{
		while (check_eat_num(&philo.eat_num))
		{
			time = time_now();
			if (eat_ph(&philo, time))
				break ;
			if (sl_th_ph(&philo, time))
				break ;
			philo.t += time_now() - time;
		}
	}
	else
		printf("0 1 philo took 1 fork\n%d %d philo died\n", \
		philo.die, philo.p);
	usleep(philo.die * 1000);
	*philo.death = 1;
	return (NULL);
}
