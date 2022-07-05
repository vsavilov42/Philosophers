#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int	error_arg_msg(void);
int	parse(t_philo **philo, char **argv);
int	parse_no_num(char **argv);
size_t	get_time(void);
void	init_philos(t_philo *philo);
void	parse_arg(t_philo **philo, char **argv);
void	create_philo(t_philo **philo);
void	philos_table(t_philo **philo, t_table *table, int n_rep);
void	printer_state(t_philo *philo, int state);
void	*philo_cycle(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo, size_t t_slp);

void	leaks(void);

#endif
