/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:09:54 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:31:02 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_countword(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

static char	**ft_split_check(const char *s, char c)
{
	char	**split_tab;

	split_tab = NULL;
	if (!s)
		return (NULL);
	split_tab = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!split_tab)
		return (NULL);
	return (split_tab);
}

static char	*ft_write(const char *s, int *i, char c)
{
	int		k;
	int		u;
	int		o;
	char	*word;

	k = *i;
	u = *i;
	o = 0;
	while (s[k] != c && s[k] != '\0')
		k++;
	word = malloc((k - u + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (s[u] != c && s[u] != '\0')
	{
		word[o] = s[u];
		o++;
		u++;
	}
	word[o] = '\0';
	*i = k;
	return (word);
}

static char	**ft_free(char **split_tab, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(split_tab[i]);
		i++;
	}
	free(split_tab);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	char	**split_tab;
	int		j;

	j = 0;
	i = 0;
	split_tab = ft_split_check(s, c);
	if (!split_tab)
		return (NULL);
	while (i < (int)ft_strlen(s))
	{
		if (s[i] != c)
		{
			split_tab[j] = ft_write(s, &i, c);
			if (!split_tab[j])
				return (ft_free(split_tab, j));
			j++;
		}
		i++;
	}
	split_tab[j] = NULL;
	return (split_tab);
}
