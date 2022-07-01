#include <Philosophers.h>

int main(int argc, char **argv)
{
	t_philo	**philo;

	//atexit(leaks);
	if (argc < 5 || argc > 6)
		return (error_arg_msg());
	philo = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!parse(philo, argv)) {
		life_cycle(philo);
	}
	free(philo);
	return (0);
}

void	leaks(void)
{
	system("leaks -q philo");
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
//	printf("[Thread_philo -> (%p)]", philo);
	if (philo->p_id % 2 == 0)
		usleep(1000);
//	printf(" // P_ID [Thread ID (%d)]\n", philo->p_id);
	while (philo->table->dead == 0)
	{
		//eat(philo);
		msg_cycle(philo, "is sleeping");
		usleep(philo->table->t_slp);
		msg_cycle(philo, "is thinking");
	}
	return (NULL);
}

void	msg_cycle(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->msg);
	if (philo->table->dead == 0)
	{
		printf("%6ld ms, Philo->%d %s\n", philo->time, philo->p_id, msg);
	}
	pthread_mutex_unlock(&philo->msg);
}


void	create_philo(t_philo **philo)
{
	int	p_tmp;
	int	total_filo;

	total_filo = philo[0]->table->n_phl;
	p_tmp = -1;
	while (++p_tmp < total_filo)
	{
		printf("dead == %d\n", (*philo)->table->dead);
		if (pthread_create(philo[p_tmp]->id, NULL, &philo_cycle, philo[p_tmp]))
		{
			printf("ERROR\n");
		}

	}
}

void	life_cycle(t_philo **philo)
{
	create_philo(philo);
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
	t_philo	*tmp;
	t_philo	*start;

	i = -1;
	start = *philo;
	while (++i < table->n_phl)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		philo[i]->id = (pthread_t *)malloc(table->n_phl * sizeof(pthread_t));
		philo[i]->p_id = i + 1;
		philo[i]->table = table;
		philo[i]->time = get_time();
		philo[i]->n_rep = n_rep;
		pthread_mutex_init(&philo[i]->fork, NULL);
		pthread_mutex_init(&philo[i]->msg, NULL);
		if (i == table->n_phl - 1)
			philo[i]->right = start;
		else
			philo[i]->right = tmp;
		tmp = philo[i];
	}
}

void	parse_arg(t_philo **philo, char **argv)
{
	t_table	table;
	int	n_rep;

	table.n_phl = ft_atoi(argv[1]);
	table.t_die = ft_atoi(argv[2]);
	table.t_eat = ft_atoi(argv[3]);
	table.t_slp = ft_atoi(argv[4]);
	table.dead = 0;
	if (argv[5] == NULL)
		n_rep = -1;
	else
		n_rep = ft_atoi(argv[5]);
	philos_table(philo, &table, n_rep);
}

size_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 1000));
}

int	error_arg_msg()
{
	write(1, "Usage: num of philo; time to die; time to eat; time to sleep; [optional] number of times each philo eats\n", 105);
	return (0);
}
