/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcorina <pcorina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:58:54 by pcorina           #+#    #+#             */
/*   Updated: 2022/03/11 15:59:12 by pcorina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo			philo;
	int				death;
	int				init_check;

	if (argc > 4 && argc < 7)
	{
		init_check = init_philo(&philo, argv, argc);
		if (init_check == 1)
			return (write(2, "ERROR bad arg\n", 14));
		else if (init_check == -1)
			return (write(2, "ERROR, Memory\n", 14));
		if (argc == 6)
			philo.eat_num = ft_atoi(argv[5]);
		else
			philo.eat_num = -1;
		creating_streams(&philo);
		free(philo.thread);
		free(philo.pid);
		sem_unlink("forks");
		sem_unlink("print");
	}
	else
		write(2, "ERROR bad number of arguments\n", 30);
	return (0);
}
