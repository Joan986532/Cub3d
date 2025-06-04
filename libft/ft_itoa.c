/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:53:17 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:30:30 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_nlen(long long int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		count++;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_putnbr(long long int n)
{
	long long int	nbis;

	nbis = n;
	nbis %= 10;
	return (nbis + 48);
}

static char	*write_itoa(char *number, long long int n2, int size)
{
	int	i;

	i = 0;
	if (n2 < 0)
	{
		n2 *= (-1);
		number[i] = '-';
	}
	while (i < size)
	{
		if (number[size - i - 1] != '-')
		{
			number[size - i - 1] = ft_putnbr(n2);
			n2 /= 10;
		}
		i++;
	}
	number[i] = '\0';
	return (number);
}

char	*ft_itoa(int n)
{
	char			*number;
	size_t			size;
	long long int	n2;

	n2 = n;
	size = ft_nlen(n2);
	if (n2 < -2147483648 || n2 > 2147483647)
		return (NULL);
	number = ft_calloc((size + 1), sizeof(char));
	if (!number)
		return (NULL);
	return (write_itoa(number, n2, size));
}
