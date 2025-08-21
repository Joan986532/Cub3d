/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npapashv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:49:23 by npapashv          #+#    #+#             */
/*   Updated: 2025/08/21 10:49:24 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_new(t_list *new, char *str, t_list *root)
{
	if (new)
		return (0);
	free(str);
	ft_lstclear(&root, free);
	return (-1);
}

t_list	*get_linked_map(int fd, char *str)
{
	t_list	*root;
	t_list	*current;
	t_list	*new;

	root = ft_lstnew(str);
	if (!root)
		return (NULL);
	current = root;
	while (1)
	{
		str = get_next_line_no_nl(fd);
		if (!str)
		{
			free(str);
			break ;
		}
		new = ft_lstnew(str);
		if (check_new(new, str, root) != 0)
			return (NULL);
		ft_lstadd_back(&current, new);
		current = new;
	}
	return (root);
}

void	fill_line(t_datamap *map, int i, char *str)
{
	int	j;

	j = 0;
	while (j < map->map_width)
	{
		map->map[i][j] = ' ';
		if (is_spawn(*str))
			set_spawn(map->player, *str, i, j);
		if (*str)
		{
			map->map[i][j] = *str;
			++str;
		}
		++j;
	}
	map->map[i][j] = '\0';
}

void	fill_map(t_list *linked_map, t_datamap *map)
{
	t_list	*current;
	int		i;

	i = 0;
	current = linked_map;
	while (current)
	{
		map->map[i] = malloc(sizeof(char *) * (map->map_width + 1));
		if (!map->map[i])
			break ;
		fill_line(map, i, (char *)current->content);
		current = current->next;
		i++;
	}
	if (current)
	{
		free_arr(map->map);
		map->map = NULL;
	}
	ft_lstclear(&linked_map, free);
}

int	parse_map(char *str, t_datamap *map, int fd)
{
	t_list	*linked_map;
	int		i;

	if (map->map)
		return (parsing_error(SYNTAX, map));
	str = ft_strdup(str);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
	linked_map = get_linked_map(fd, str);
	if (!linked_map)
		return (-1);
	set_map_dimensions(linked_map, map);
	map->map = (char **)malloc(sizeof(char *) * (map->map_height + 1));
	if (!map->map)
	{
		ft_lstclear(&linked_map, free);
		return (-1);
	}
	map->map[map->map_height] = NULL;
	fill_map(linked_map, map);
	return (0);
}
