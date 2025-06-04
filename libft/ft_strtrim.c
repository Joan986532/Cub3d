/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:42:19 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:32:57 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_start(char const *s1, char const *set, int i)
{
	int	j;

	j = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (set[j] == '\0')
			break ;
		i++;
	}
	return (i);
}

static int	ft_end(char const *s1, char const *set, int k, int i)
{
	int	j;

	j = 0;
	while (s1[i - k] != '\0')
	{
		j = 0;
		while (s1[i - k] != set[j] && set[j] != '\0')
			j++;
		if (set[j] == '\0')
			break ;
		k++;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		k;
	char	*ft_trim;
	int		size_s1;

	ft_trim = NULL;
	i = 0;
	k = 0;
	if (s1 == NULL || set == NULL)
		return (0);
	size_s1 = ft_strlen(s1);
	i = ft_start(s1, set, i);
	if (s1[i] == '\0')
		return (ft_calloc(sizeof(char), 1));
	k = ft_end(s1, set, k, (size_s1 - 1));
	ft_trim = ft_calloc(sizeof(char), (size_s1 - k - i + 1));
	if (ft_trim)
		ft_memcpy(ft_trim, (s1 + i), (size_s1 - k - i));
	return (ft_trim);
}
