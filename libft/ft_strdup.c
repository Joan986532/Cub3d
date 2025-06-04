/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:24:54 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/23 19:33:03 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char	*s)
{
	int		size;
	char	*ft_s;
	int		i;

	i = 0;
	ft_s = NULL;
	size = ft_strlen(s);
	ft_s = malloc((size + 1) * sizeof(char));
	if (!ft_s)
		return (0);
	while (s[i])
	{
		ft_s[i] = s[i];
		i++;
	}
	ft_s[i] = '\0';
	return (ft_s);
}
