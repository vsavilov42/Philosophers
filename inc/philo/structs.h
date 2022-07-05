#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_table
{
	int		n_phl;
	int		t_die;
	int		t_eat;
	int		t_slp;
	int		full_eat;
	int		all_eat;
	int		dead;
}	t_table;

typedef struct s_philo
{	
	pthread_t	*id;
	size_t		time;
	int		p_id;
	int		p_dead;
	int		n_rep;
	pthread_mutex_t	fork;
	pthread_mutex_t	msg;
	struct		s_philo *right;
	struct		s_table *table;
}	t_philo;

#endif
