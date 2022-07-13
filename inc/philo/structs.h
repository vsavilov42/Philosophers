#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_table
{
	int		n_phl;
	int		t_die;
	int		t_eat;
	int		t_slp;
	size_t		time;
	int		all_eat;
	pthread_mutex_t	death;
	int		dead;
}	t_table;

typedef struct s_philo
{	
	pthread_t	*id;
	size_t		t_diff_eat;
	int		p_id;
	int		n_rep;
	pthread_mutex_t	fork;
	pthread_mutex_t	msg;
	struct		s_philo *right;
	struct		s_table *table;
}	t_philo;

#endif
