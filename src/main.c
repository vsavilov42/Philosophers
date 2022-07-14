/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:01:18 by vsavilov          #+#    #+#             */
/*   Updated: 2022/07/14 17:30:43 by Vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Philosophers.h>

int	main(int argc, char **argv)
{
	t_philo	**philo;

	philo = NULL;
	if (argc < 5 || argc > 6)
		return (error_arg_msg());
	philo = (t_philo **)malloc(sizeof(t_philo *) * ft_atoi(argv[1]));
	if (!parse(philo, argv))
	{
		printf("%d\n", ft_atoi(argv[1]));
		create_philo(philo);
		free_all(philo, (*philo)->table->n_phl);
	}
	free(philo);
	return (0);
}
