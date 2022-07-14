/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:01:10 by vsavilov          #+#    #+#             */
/*   Updated: 2022/07/14 13:19:47 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

/* parse.c */

int		parse(t_philo **philo, char **argv);
int		parse_no_num(char **argv);
void	parse_arg(t_philo **philo, char **argv);

/* philo.c */

void	philos_table(t_philo **philo, t_table *table, int n_rep);
void	create_philo(t_philo **philo);
void	*philo_cycle(void *arg);
void	philo_eat(t_philo *philo);
void	dead_check(t_philo **philo, int total_philo);

/* philo_utils.c */

size_t	get_time(void);
void	free_all(t_philo **philo, int n_phl);
void	philo_sleep(t_philo *philo, size_t t_slp);

/* printer.c */

int		error_arg_msg(void);
void	printer_state(t_philo *philo, int state);

/* libft_utils.c */

int		ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif
