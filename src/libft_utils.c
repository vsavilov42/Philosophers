/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavilov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:01:23 by vsavilov          #+#    #+#             */
/*   Updated: 2022/07/14 13:19:29 by vsavilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Philosophers.h>

int	ft_atoi(const char *str)
{
	int		negative;
	size_t	i;

	i = 0;
	negative = 1;
	while ((*str >= 0x09 && *str <= 0x0d) || (*str == 0x20))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = (i * 10) + (*str - '0');
		if (i > 2147483647 && negative == 1)
			return (-1);
		if (i > 2147483648 && negative == -1)
			return (0);
		str++;
	}
	return (negative * i);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
