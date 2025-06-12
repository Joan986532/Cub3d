#include "cub3d.h"

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
        if (!str || str[0] == '\0' || str[0] == '\n')
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

void    set_spawn(t_player *player, char c, int i, int j)
{
    player->spawn = (t_vector3D){j, i, 0};
    player->pos = player->spawn;
    if (c == 'N')
        player->spawn_fwd = (t_vector3D){0, -1, 0};
    else if (c == 'S')
        player->spawn_fwd = (t_vector3D){0, 1, 0};
    else if (c == 'E')
        player->spawn_fwd = (t_vector3D){1, 0, 0};
    else if (c == 'W')
        player->spawn_fwd = (t_vector3D){-1, 0, 0};
    player->fwd = player->spawn_fwd;
}

void    fill_line(t_datamap *map, int i, char *str)
{
    int     j;

    j = 0;
    while (j < map->map_width)
    {
        map->map[i][j] = ' ';
        if (is_spawn(*str))
            set_spawn(map->global->player, *str, i, j);
        if (*str)
        {
            map->map[i][j] = *str;
            ++str;
        }
        ++j;
    }
    map->map[i][j] = '\0';
}

void fill_map(t_list *linked_map, t_datamap *map)
{
    t_list  *current;
    int     i;

    i = 0;
    current = linked_map;
    while (current)
    {
        map->map[i] = malloc(sizeof(char *) * (map->map_width + 1));
        if (!map->map[i])
            break;
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

void    set_map_dimensions(t_list *linked_map, t_datamap *map)
{
    int current_width;
    int width;
    int height;

    width = 0;
    height = 0;
    while (linked_map)
    {
        current_width = ft_strlen((char *)linked_map->content);
        if (current_width > width)
            width = current_width;
        ++height;
        linked_map = linked_map->next;
    }
    map->map_width = width;
    map->map_height = height;
}

int parse_map(char *str, t_datamap *map, int fd)
{
    t_list  *linked_map;
    int     i;

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