#include <Philosophers.h>

int main(int argc, char **argv)
{
	t_philo	**philo;

	if (argc < 5 || argc > 6)
		return (error_arg_msg());
	philo = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!parse(philo, argv))
		create_philo(philo);
	free_all(philo, (*philo)->table->n_phl);
	return (0);
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
	free(philo);
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	printer_state(philo, 0);
	if (philo->table->n_phl == 1)
		return ;
	pthread_mutex_lock(&philo->right->fork);
	printer_state(philo, 0);
	philo->t_diff_eat = get_time();
	printer_state(philo, 1);
	philo_sleep(philo, (size_t)philo->table->t_slp);
	if (philo->n_rep != -1)
		philo->table->all_eat++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->right->fork);
	printer_state(philo, 2);
	philo_sleep(philo, (size_t)philo->table->t_slp);
	printer_state(philo, 3);
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

void	printer_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->msg);
	if (philo->table->dead)
	{
		if (state == 0)
			printf("%lu ms, philo %d, has taken a fork.\n",
				get_time() - philo->time, philo->p_id);
		if (state == 1)
			printf("%lu ms, philo %d, is eating.\n",
				get_time() - philo->time, philo->p_id);
		if (state == 2)
			printf("%lu ms, philo %d, is sleeping.\n",
				get_time() - philo->time, philo->p_id);
		if (state == 3)
			printf("%lu ms, philo %d, is thinking.\n",
				get_time() - philo->time, philo->p_id);
	}
	if (state == 4)
		printf("%lu ms, philo %d, died.\n",
			get_time() - philo->time, philo->p_id);
	pthread_mutex_unlock(&philo->msg);
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
		if (get_time() - philo[p_tmp]->t_diff_eat >= (size_t)(*philo)->table->t_eat)
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
	/*p_tmp = -1;
	while (++p_tmp < total_philo)
		pthread_mutex_destroy(&philo[p_tmp]->fork);
*/
}

int	parse(t_philo **philo, char **argv)
{
	if (!parse_no_num(argv))
	{
		parse_arg(philo, argv);
		return (0);
	}
	return (1);
}

int	parse_no_num(char **argv)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	while (argv[j][i])
	{
		i = 0;
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

void	philos_table(t_philo **philo, t_table *table, int n_rep)
{
	int	i;

	i = -1;
	while (++i < table->n_phl)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->id = (pthread_t *)malloc(sizeof(pthread_t));
		philo[i]->time = get_time();
		philo[i]->t_diff_eat = 0;
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

void	parse_arg(t_philo **philo, char **argv)
{
	t_table	*table;
	int	n_rep;

	table = (t_table *)malloc(sizeof(t_table));
	table->n_phl = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_slp = ft_atoi(argv[4]);
	table->all_eat = 0;
	table->dead = 1;
	if (argv[5] == NULL)
		n_rep = -1;
	else
		n_rep = ft_atoi(argv[5]);
	pthread_mutex_init(&table->death, NULL);
	philos_table(philo, table, n_rep);
}

size_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	error_arg_msg()
{
	write(1, "Usage: num of philo; time to die; time to eat; time to sleep; [optional] number of times each philo eats\n", 105);
	return (0);
}
