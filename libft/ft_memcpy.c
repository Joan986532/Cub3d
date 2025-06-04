/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:30:25 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:44:42 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*chardest;
	const char	*charsrc;

	if (!dest && !src)
		return (NULL);
	chardest = (char *) dest;
	charsrc = (char *) src;
	i = 0;
	while (i < n)
	{
		chardest[i] = charsrc[i];
		i++;
	}
	return (dest);
}
