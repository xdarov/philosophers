/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 18:05:14 by pcorina           #+#    #+#             */
/*   Updated: 2022/03/09 19:41:12 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct s_philo
{
	int					num_philo;
	int					die;
	int					eat;
	int					sleep;
	int					num_eat;
	pthread_mutex_t		*mut;
	pthread_t			*thread;

	long				start_eat;
	int					eat_num;
	int					m1;
	int					m2;
	int					p;
	long				t;
	int					*death;
}		t_philo;

int		init_philo(t_philo *philo, char **argv, int argc);
t_philo	*init_var(void *link);
long	time_now(void);
void	output(t_philo *philo, char *str, long time);
int		check_death(t_philo *philo, long time);
int		eat_ph(t_philo *philo, long time);
int		sl_th_ph(t_philo *philo, long time);
void	*philo_life(void *link);
void	creating_streams(t_philo *philo);
int		check_eat_num(int *eat_num);

#endif