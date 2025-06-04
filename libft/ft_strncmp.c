/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:15:52 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:46:43 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*ft_s1;
	unsigned char	*ft_s2;

	i = 0;
	ft_s1 = (unsigned char *)s1;
	ft_s2 = (unsigned char *)s2;
	while (i < n && (ft_s1[i] != '\0' || ft_s2[i] != '\0'))
	{
		if (ft_s1[i] != ft_s2[i])
			return (ft_s1[i] - ft_s2[i]);
		i++;
	}
	return (0);
}
