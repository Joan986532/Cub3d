#include "headers/cub3d.h"

int	choose_color_surface(int nb, char c, t_datamap *map)
{
	if (c == 'C')
		map->ceiling = nb;
	else if (c == 'F')
		map->floor = nb;
	else
	{
		return (parsing_error(SYNTAX, map->global));
	}
	return (0);
}

int	rgb_to_color(unsigned char r, unsigned char g, unsigned char b)
{
	int	color;

	color = 0;
	color |= r << 16;
	color |= g << 8;
	color |= b;
	return (color);
}

int	convert_color(char *str, int *i, t_datamap *map)
{
	int	nb;

	nb = 0;
	while (str[*i] && ft_isdigit(str[*i]))
	{
		if (nb > UCHAR_MAX / 10)
			return (parsing_error(LIMITCOLOR, map->global));
		nb *= 10;
		if (nb > UCHAR_MAX + (str[*i] - 48))
			return (parsing_error(LIMITCOLOR, map->global));
		nb += str[*i] - 48;
		(*i)++;
	}
	if (str[*i] == ',')
		i++;
	return (nb);
}

//identifier
int	iscolor(char *str, t_datamap *map)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				i;
	int				nb;

	i = 0;
	nb = 0;
	while (!ft_isdigit(str[i]))
		i++;
	r = convert_color(str, &i, map);
	g = convert_color(str, &i, map);
	b = convert_color(str, &i, map);
	if (r < 0 || g < 0 || b < 0)
		return (parsing_error(LIMITCOLOR, map->global));
	nb = rgb_to_color(r, g, b);
	choose_color_surface(nb, str[0], map);
	return (0);
}
