#include <Philosophers.h>

size_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	free_all(t_philo **philo, int n_phl)
{
	int	i;

	i = -1;
	free((*philo)->table);
	while (++i < n_phl)
	{
		free(philo[i]->id);
		free(philo[i]);
	}
}

void	philo_sleep(t_philo *philo, size_t t_slp)
{
	size_t	time;

	time = get_time();
	while (philo->table->dead)
	{
		if ((get_time() - time) >= t_slp)
			break ;
		usleep(100);
	}
}
