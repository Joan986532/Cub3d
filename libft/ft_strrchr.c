/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:05:00 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:01:32 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ft_s;

	i = ft_strlen(s);
	ft_s = (char *)s;
	while (i >= 0)
	{
		if (ft_s[i] == (unsigned char)c)
			return (&ft_s[i]);
		i--;
	}
	return (NULL);
}
