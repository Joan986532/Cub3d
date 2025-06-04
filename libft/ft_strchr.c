/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:21:10 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:14:55 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*ft_s;

	i = 0;
	ft_s = (char *)s;
	while (i <= ft_strlen(ft_s))
	{
		if (ft_s[i] == (unsigned char)c)
			return (&ft_s[i]);
		i++;
	}
	return (NULL);
}
