/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:36:04 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:42:49 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief DDA algorithnm.
 *
 * This function executes the operations necessary for the DDA algorithm. It
 * will loop until the ray "touches" a wall. At each step, it calculates the
 * distance to the next x and y side of the grid cell, and determines which
 * direction the ray should move based on these distances.
 *
 * @param game game structure.
 * @param player structure containing player data.
 * @param ray structure containing ray data.
 */
void	dda_algo(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25
			|| ray->map_y > game->input->map_height - 0.25
			|| ray->map_x > game->input->map_width - 1.25)
			break ;
		if (game->input->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

/**
 * @brief Init the DDA.
 *
 * This function initializes the DDA (Digital Differential Analyzer) before we
 * can actually start using this algorithm. To do so, we have to calculate
 * some values (step_x, step_y, side_dist_x, side_dist_y). The step values are
 * based on the sign (- OR +) of the ray direction. The side_dist values
 * represent the perpendicular distance from the ray's starting position to the
 * nearest side of the wall it touches (adjusted and base and ray's direction
 * and position).
 *
 * @param game game structure.
 * @param player structure containing player data.
 * @param ray structure containing ray data.
 */
void	init_dda(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((player->pos_x - ray->map_x) * ray->delta_dist_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1.0 - player->pos_x)
				* ray->delta_dist_x);
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((player->pos_y - ray->map_y) * ray->delta_dist_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1.0 - player->pos_y)
				* ray->delta_dist_y);
	}
}

/**
 * @brief Wall height calculation.
 *
 * This function calculates the height of the wall given the info gathered with
 * the ray. To avoid getting a warped view (fisheye effect), the distance to the
 * wall isn't always calculated starting from player position, but rather it is
 * calculated relatively to the camera plane (what we view when playing). To do
 * so we calculate the shortest distance from a point (where the ray hit the
 * wall) to a line (the camera plane).
 *
 * @param game game structure.
 * @param player structure containing player data.
 * @param ray structure containing ray data.
 * @param draw structure containing data to draw.
 */
void	calc_wall_height(t_player *player, t_ray *ray, t_draw *draw)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	draw->wall_height = (int)(WIN_H / ray->perp_wall_dist);
	draw->start = -(draw->wall_height) / 2 + WIN_H / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->wall_height / 2 + WIN_H / 2;
	if (draw->end >= WIN_H)
		draw->end = WIN_H - 1;
	if (ray->side == 0)
		draw->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		draw->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
}
