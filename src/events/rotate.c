/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:54:02 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:58:24 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rotate_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y
		* sin(-ROT_SPEED);
	player->dir_y = old_dir_x * sin(-ROT_SPEED) + player->dir_y
		* cos(-ROT_SPEED);
	player->plane_x = player->plane_x * cos(-ROT_SPEED) - player->plane_y
		* sin(-ROT_SPEED);
	player->plane_y = old_plane_x * sin(-ROT_SPEED) + player->plane_y
		* cos(-ROT_SPEED);
	return (1);
}

int	rotate_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y
		* sin(ROT_SPEED);
	player->dir_y = old_dir_x * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
	player->plane_x = player->plane_x * cos(ROT_SPEED) - player->plane_y
		* sin(ROT_SPEED);
	player->plane_y = old_plane_x * sin(ROT_SPEED) + player->plane_y
		* cos(ROT_SPEED);
	return (1);
}
