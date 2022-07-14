#include <Philosophers.h>

void	parse_arg(t_philo **philo, char **argv)
{
	t_table	*table;
	int	n_rep;

	table = (t_table *)malloc(sizeof(t_table));
	table->n_phl = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_slp = ft_atoi(argv[4]);
	table->time = get_time();
	table->all_eat = 0;
	table->dead = 1;
	if (argv[5] == NULL)
		n_rep = -1;
	else
		n_rep = ft_atoi(argv[5]);
	pthread_mutex_init(&table->death, NULL);
	philos_table(philo, table, n_rep);
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

int	parse(t_philo **philo, char **argv)
{
	if (!parse_no_num(argv))
	{
		parse_arg(philo, argv);
		return (0);
	}
	return (1);
}
