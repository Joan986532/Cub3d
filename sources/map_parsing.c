#include "cub3d.h"

void	dummy_del(void *content)
{
	(void)content;
}

char    *get_next_line_no_nl(int fd)
{
    char    *str;
    int     i;

    str = get_next_line(fd);
    if (!str)
        return (NULL);
    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    str[i] = '\0';
    return (str);
}

t_list  *get_linked_map(int fd, char *str)
{
    t_list  *root;
    t_list  *current;
    t_list  *new;

    str[ft_strlen(str) - 1] = '\0';
    root = ft_lstnew(str);
    if (!root)
        return (NULL);
    current = root;
    while (1)
    {
        str = get_next_line_no_nl(fd);
        if (!str)
            break ;
        new = ft_lstnew(str);
        if (!new)
        {
            ft_lstclear(&root, free);
            return (NULL);
        }
        ft_lstadd_back(&current, new);
        current = new;
    }
    return (root);
}

int parse_map(char *str, t_datamap *map, int fd)
{
    t_list  *linked_map;
    t_list  *current;
    int     i;

    str = ft_strdup(str);
    if  (map->map)
        return (parsing_error(SYNTAX, map->global));
    linked_map = get_linked_map(fd, str);
    if (!linked_map)
        return (-1);
    map->map = (char **)malloc(sizeof(char *) * (ft_lstsize(linked_map) + 1));
    if (!map->map)
    {
        ft_lstclear(&linked_map, free);
        return (-1);
    }
    current = linked_map;
    i = 0;
    while (current)
    {
        map->map[i] = (char *)current->content;
        current = current->next;
        i++;
    }
    map->map[i] = NULL;
    ft_lstclear(&linked_map, dummy_del);
    return (0);
}