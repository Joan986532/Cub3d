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

void fill_map(t_list *linked_map, t_datamap *map)
{
    t_list  *current;
    int     i;
    int     j;

    current = linked_map;
    i = 0;
    while (current)
    {
        map->map[i] = (char *)current->content;
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == ' ' || map->map[i][j] == '\t')
                map->map[i][j] = '1';
            j++;
        }
        current = current->next;
        i++;
    }
    map->map[i] = NULL;
    ft_lstclear(&linked_map, dummy_del);
}

int parse_map(char *str, t_datamap *map, int fd)
{
    t_list  *linked_map;
    int     i;
    int     size;

    str = ft_strdup(str);
    i = 0;
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    str[i] = '\0';
    if  (map->map)
        return (parsing_error(SYNTAX, map->global));
    linked_map = get_linked_map(fd, str);
    if (!linked_map)
        return (-1);
    size = ft_lstsize(linked_map);
    map->map = (char **)malloc(sizeof(char *) * (size + 1));
    if (!map->map)
    {
        ft_lstclear(&linked_map, free);
        return (-1);
    }
    map->map_height = size;
    fill_map(linked_map, map);
    return (0);
}