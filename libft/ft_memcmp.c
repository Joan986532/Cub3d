/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:23:39 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:47:27 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t n)
{
	unsigned char	*ft_s1;
	unsigned char	*ft_s2;
	size_t			i;

	i = 0;
	ft_s1 = (unsigned char *)s1;
	ft_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (ft_s1[i] != ft_s2[i])
			return (ft_s1[i] - ft_s2[i]);
		i++;
	}
	return (0);
}
