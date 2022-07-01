#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int	error_arg_msg(void);
int	parse(t_philo **philo, char **argv);
int	parse_no_num(char **argv);
size_t	get_time(void);
void	init_philos(t_philo *philo);
void	parse_arg(t_philo **philo, char **argv);
void	life_cycle(t_philo **philo);
void	create_philo(t_philo **philo);
void	philos_table(t_philo **philo, t_table *table, int n_rep);
void	msg_cycle(t_philo *philo, char *msg);
void	*philo_cycle(void *arg);

void	leaks(void);

#endif
