/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:01:48 by vsavilov          #+#    #+#             */
/*   Updated: 2022/07/14 13:28:10 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Philosophers.h>

int	error_arg_msg(void)
{
	write(1, "Usage: num of philo; time to die; time to eat; time to", 54);
	write(1, " sleep; [optional] number of times each philo eats\n", 52);
	return (0);
}

void	printer_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->msg);
	if (philo->table->dead)
	{
		if (state == 0)
			printf("%lu ms, philo %d, has taken a fork.\n",
				get_time() - philo->table->time, philo->p_id);
		if (state == 1)
			printf("%lu ms, philo %d, is eating.\n",
				get_time() - philo->table->time, philo->p_id);
		if (state == 2)
			printf("%lu ms, philo %d, is sleeping.\n",
				get_time() - philo->table->time, philo->p_id);
		if (state == 3)
			printf("%lu ms, philo %d, is thinking.\n",
				get_time() - philo->table->time, philo->p_id);
	}
	if (state == 4)
		printf("%lu ms, philo %d, died.\n",
			get_time() - philo->table->time, philo->p_id);
	pthread_mutex_unlock(&philo->msg);
}
