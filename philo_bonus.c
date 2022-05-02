/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 21:01:04 by pcorina           #+#    #+#             */
/*   Updated: 2022/03/11 16:32:30 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	philo->thread = malloc(sizeof(pthread_t *) * philo->num_philo);
	if (!philo->thread)
		return (-1);
	sem_unlink("forks");
	philo->sem = sem_open("forks", O_CREAT, 0660, 0);
	i = -1;
	while (++i < philo->num_philo)
		sem_post(philo->sem);
	return (0);
}

void	creating_streams(t_philo *philo)
{
	int	i;

	sem_unlink("print");
	philo->out = sem_open("print", O_CREAT, 0660, 0);
	sem_post(philo->out);
	philo->pid = malloc(sizeof(pid_t) * philo->num_philo);
	if (philo->num_philo > 0)
	{
		i = -1;
		while (++i < philo->num_philo)
		{
			philo->p = i + 1;
			philo->pid[i] = fork();
			if (!philo->pid[i])
			{
				philo_life(philo);
				return ;
			}
		}
		wait(&i);
		i = -1;
		while (++i < philo->num_philo)
			kill(philo->pid[i], SIGTERM);
	}
}

int	eat_ph(t_philo *philo, long time)
{
	sem_wait(philo->sem);
	output(philo, "took 1 fork", time_now() - time);
	sem_wait(philo->sem);
	output(philo, "took 2 fork", time_now() - time);
	output(philo, "eat", time_now() - time);
	philo->start_eat = time_now();
	while (philo->eat + philo->start_eat > time_now())
	{
		usleep(100);
		if (check_death(philo, time_now() - philo->start_eat))
			return (1);
	}
	usleep(100);
	sem_post(philo->sem);
	sem_post(philo->sem);
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

void	philo_life(t_philo *philo)
{
	long		time;

	if (check_death(philo, 0))
		return ;
	if (philo->num_philo != 1)
	{
		while (check_eat_num(&philo->eat_num))
		{
			time = time_now();
			if (eat_ph(philo, time))
				break ;
			if (sl_th_ph(philo, time))
				break ;
			philo->t += time_now() - time;
		}
	}
	else
		printf("0 1 philo took 1 fork\n%d %d philo died\n", \
		philo->die, philo->p);
	usleep(philo->die * 1000);
	return ;
}

//ps aux | grep "philo_b"