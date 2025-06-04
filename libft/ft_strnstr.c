/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:52:11 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:48:00 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		n = 0;
		while (little[n] == big[n + i])
		{
			n++;
			if (little[n] == '\0')
				return ((char *)&big[i]);
			if (i + n == len)
				return (NULL);
		}
		i++;
	}
	return (NULL);
}
