/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:10:04 by jnauroy           #+#    #+#             */
/*   Updated: 2024/10/23 19:11:40 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmpbis;

	tmp = *lst;
	if (!*lst || !del)
		return ;
	while (tmp)
	{
		tmpbis = tmp;
		del(tmpbis->content);
		tmp = tmp->next;
		free(tmpbis);
	}
	*lst = NULL;
}
