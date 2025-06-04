/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:12:43 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/14 18:40:03 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ft_join;
	int		i;
	int		j;
	int		size_s1;
	int		size_s2;

	i = 0;
	j = 0;
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	ft_join = NULL;
	ft_join = malloc((size_s1 + size_s2 + 1) * sizeof(char));
	if (!ft_join)
		return (0);
	while (i < size_s1 + size_s2)
	{
		if (i < size_s1)
			ft_join[i] = s1[i];
		if (i >= size_s1 && i < size_s1 + size_s2)
			ft_join[i] = s2[j++];
		i++;
	}
	ft_join[i] = '\0';
	return (ft_join);
}
