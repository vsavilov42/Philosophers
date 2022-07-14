#include <Philosophers.h>

void	philos_table(t_philo **philo, t_table *table, int n_rep)
{
	int	i;

	i = -1;
	while (++i < table->n_phl)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->id = (pthread_t *)malloc(sizeof(pthread_t));
		philo[i]->t_diff_eat = table->time;
		philo[i]->p_id = i + 1;
		philo[i]->n_rep = n_rep;
		pthread_mutex_init(&philo[i]->fork, NULL);
		pthread_mutex_init(&philo[i]->msg, NULL);
		philo[i]->table = table;
	}
	i = -1;
	while (++i < table->n_phl - 1)
		philo[i]->right = philo[i + 1];
	philo[i]->right = philo[0];
}

void	create_philo(t_philo **philo)
{
	int	p_tmp;
	int	total_philo;

	total_philo = (*philo)->table->n_phl;
	p_tmp = -1;
	while (++p_tmp < total_philo)
		if (pthread_create(philo[p_tmp]->id, NULL, &philo_cycle, philo[p_tmp]))
			printf("ERROR\n");
	while ((*philo)->table->dead)
	{
		if (p_tmp == total_philo)
			p_tmp = 0;
		pthread_mutex_lock(&(*philo)->table->death);
		if (get_time() - philo[p_tmp]->t_diff_eat >= (size_t)(*philo)->table->t_die)
		{
			philo[p_tmp]->table->dead = 0;
			printer_state(philo[p_tmp], 4);
		}
		pthread_mutex_unlock(&(*philo)->table->death);
		usleep(100);
		p_tmp++;
	}
	p_tmp = -1;
	while (++p_tmp < total_philo)
		pthread_join(*(philo[p_tmp]->id), NULL);
	p_tmp = -1;
	while (++p_tmp < total_philo)
		pthread_mutex_destroy(&philo[p_tmp]->fork);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->p_id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->table->death);
		if (philo->table->dead == 0)
		{
			pthread_mutex_unlock(&philo->table->death);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death);
		if ((philo->n_rep != -1) &&
			philo->table->all_eat >= (philo->table->n_phl * philo->n_rep))
			return (NULL);
		philo_eat(philo);
		if (philo->table->n_phl == 1)
			return (NULL);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer_state(philo, 0);
	if (philo->table->n_phl == 1)
		return ;
	pthread_mutex_lock(&philo->right->fork);
	printer_state(philo, 0);
	printer_state(philo, 1);
	philo->t_diff_eat = get_time();
	philo_sleep(philo, (size_t)philo->table->t_slp);
	if (philo->n_rep != -1)
		philo->table->all_eat++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	printer_state(philo, 2);
	philo_sleep(philo, (size_t)philo->table->t_slp);
	printer_state(philo, 3);
}
