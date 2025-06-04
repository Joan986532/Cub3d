/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:37:43 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:47:02 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ft_s;

	ft_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ft_s[i] == (unsigned char)c)
			return ((void *)&ft_s[i]);
		i++;
	}
	return (NULL);
}
