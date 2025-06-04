/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:47:37 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:08:17 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*ft_s;

	i = 0;
	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	ft_s = malloc((len + 1) * sizeof(char));
	if (!ft_s)
		return (NULL);
	while (i < len)
	{
		ft_s[i] = s[start + i];
		i++;
	}
	ft_s[i] = '\0';
	return (ft_s);
}
