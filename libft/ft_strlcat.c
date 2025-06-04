/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:43:36 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/25 11:00:19 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	char	*word;

	i = 0;
	word = (char *)src;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size > len_dst)
		len_src += len_dst;
	else
		len_src += size;
	while (word[i] && (len_dst + 1) < size)
		dst[len_dst++] = word[i++];
	dst[len_dst] = '\0';
	return (len_src);
}
