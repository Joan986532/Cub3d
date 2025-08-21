/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npapashv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:50:20 by npapashv          #+#    #+#             */
/*   Updated: 2025/08/21 10:50:21 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_frame(void *info)
{
	t_global	*global;
	t_mlx_data	*data;

	global = (t_global *)info;
	data = global->data;
	draw_view(data, global);
	choose_direction(global->player);
	mlx_put_image_to_window(data->mlx, data->win, data->view.mlx_img, 0, 0);
	return (0);
}
