#include "cub3d_bonus.h"

void	clear_gnl(char *str, int fd)
{
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	free (str);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_strtrime(char *str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = ft_strlen(str) - 1;
	while (j > i && (str[j] == ' ' || str[j] == '\t'))
		j--;
	ft_memmove(str, str + i, j - i + 1);
	str[j - i + 1] = '\0';
}

void	clear_textures(t_datamap *map)
{
	if (map->north_t)
		free(map->north_t);
	if (map->south_t)
		free(map->south_t);
	if (map->east_t)
		free(map->east_t);
	if (map->west_t)
		free(map->west_t);
	if (map->gun)
		free(map->gun);
}

void	set_new_player_position(t_datamap *map, float *x, float *y, float step)
{
	t_player	*player;

	player = map->player;
	if (player->forwd != player->bckwd && player->right != player->left)
		step *= 0.70710678;
	*x = player->pos.x;
	*y = player->pos.y;
	*x = *x + (player->forwd - player->bckwd) * player->fwd.x * step;
	*y = *y + (player->forwd - player->bckwd) * player->fwd.y * step;
	*x = *x + (player->right - player->left) * player->plane.x * step;
	*y = *y + (player->right - player->left) * player->plane.y * step;
	if (player->trnleft == 1)
		rotate_trigo(player, player->angle);
	if (player->trnright == 1)
		rotate_antitrigo(player, player->angle);
}
