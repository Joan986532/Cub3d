/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npapashv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:48:31 by npapashv          #+#    #+#             */
/*   Updated: 2025/08/21 10:48:33 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_antitrigo(t_player *player, float angle)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(angle)
		- player->fwd.y * sinf(angle);
	player->fwd.y = x * sinf(angle)
		+ player->fwd.y * cosf(angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(angle)
		- player->plane.y * sinf(angle);
	player->plane.y = x * sinf(angle)
		+ player->plane.y * cosf(angle);
}

void	rotate_trigo(t_player *player, float angle)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(-angle)
		- player->fwd.y * sinf(-angle);
	player->fwd.y = x * sinf(-angle)
		+ player->fwd.y * cosf(-angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(-angle)
		- player->plane.y * sinf(-angle);
	player->plane.y = x * sinf(-angle)
		+ player->plane.y * cosf(-angle);
}

void	choose_direction(t_player *player)
{
	if (player->forwd == 1)
	{
		player->pos.x += player->fwd.x * 0.08;
		player->pos.y += player->fwd.y * 0.08;
	}
	if (player->bckwd == 1)
	{
		player->pos.x -= player->fwd.x * 0.08;
		player->pos.y -= player->fwd.y * 0.08;
	}
	if (player->left == 1)
	{
		player->pos.x -= player->plane.x * 0.1;
		player->pos.y -= player->plane.y * 0.1;
	}
	if (player->right == 1)
	{
		player->pos.x += player->plane.x * 0.1;
		player->pos.y += player->plane.y * 0.1;
	}
	if (player->trnleft)
		rotate_trigo(player, player->angle);
	if (player->trnright)
		rotate_antitrigo(player, player->angle);
}
