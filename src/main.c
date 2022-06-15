#include <Philosophers.h>

int main(int argc, char **argv)
{
	t_philo	*philo;
	t_table *table;

	philo = (t_philo *)malloc(sizeof(t_philo));
	table = (t_table *)malloc(sizeof(t_table));
	philo->table = table;
	if (argc < 5 || argc > 6)
		return (error_arg_msg());
	if (!parse(philo, argv))
		life_cycle(philo);
	return (0);
}

void	*philo_cycle(void *arg)
{
	(void)arg;
	return (NULL);
}

void	init_philos(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->table->n_phl)
	{
		philo->p_id = i + 1;
	}
}

void	create_philo(t_philo *philo)
{
	int	philo_tmp;

	philo_tmp = -1;
	init_philos(philo);
	while (++philo_tmp < philo->table->n_phl)
		if (pthread_create(&philo->left[philo_tmp].id, NULL, philo_cycle, &philo[philo_tmp]))
		{
			free(philo);
		}
}

void	life_cycle(t_philo *philo)
{
	if (philo->n_rep > 0)
		while (philo->n_rep != 0)
		{
			create_philo(philo);
			philo->n_rep--;
		}
	else
		while (1)
			create_philo(philo);
}

int	parse(t_philo *philo, char **argv)
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

void	parse_arg(t_philo *philo, char **argv)
{
	philo->table->n_phl = ft_atoi(argv[1]);
	philo->table->t_die = ft_atoi(argv[2]);
	philo->table->t_eat = ft_atoi(argv[3]);
	philo->table->t_slp = ft_atoi(argv[4]);
	if (argv[5] == NULL)
		philo->n_rep = -1;
	else
		philo->n_rep = ft_atoi(argv[5]);
}

int	error_arg_msg()
{
	write(1, "Usage: num of philo; time to die; time to eat; time to sleep; [optional] number of times each philo eats\n", 105);
	return (0);
}
