/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:31:52 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:41:49 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Init the ray.
 *
 * This function initializes the ray by calculating its direction and delta
 * distances (In simpler terms, the "delta distance" refers to the distance
 * between each step that the ray takes along the x and y axes as it moves
 * through the map).
 * The ray direction (ray_dir_x and ray_dir_y) depends on the player's and
 * camera's positions.
 * delta_dist_x and delta_dist_y are the distances between each step that
 * the ray takes on the x and y axis. They represent how far the ray needs to 
 * move horizontally and vertically to reach the next intersection with a grid
 * cell in the map.
 *
 * @param game game structure.
 * @param player structure containing player data.
 * @param ray structure containing ray data.
 * @param x pixel of the screen the ray is casted to.
 */
static void	start_ray(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_W - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/**
 * @brief Raycasting function.
 *
 * This function first set map_x and map_y to starting position of the player,
 * then calls the different functions to handle the raycasting. One ray is sent
 * for each pixel of the width of the screen.
 *
 * @param game game structure.
 * @param player structure containing player data.
 * @param ray structure containing ray data.
 * @param draw structure containing data to draw.
 */
static int	raycaster(t_game *game, t_player *player, t_ray *ray, t_draw *draw)
{
	int	x;

	x = 0;
	if (init_pixels_tab(game) == FAILURE)
		return (FAILURE);
	while (x < WIN_W)
	{
		start_ray(player, ray, x);
		init_dda(player, ray);
		dda_algo(game, ray);
		calc_wall_height(player, ray, draw);
		set_texture_index(ray, draw);
		if (update_tex(game, ray, draw, x) == FAILURE)
			return (FAILURE);
		x++;
	}
	return (SUCCESS);
}

/**
 * @brief Handle the raycasting.
 *
 * This function calls the functions necessary to get the player start
 * position, and start the raycasting.
 *
 * @param game game structure.
 * @return SUCCESS if raycasting worked, FAILURE if not.
 */
int	raycasting(t_game *game, int flag)
{
	if (flag == 1)
		get_player_start_pos(game, game->input->map);
	if (init_pixels_tab(game) == FAILURE)
		return (FAILURE);
	if (raycaster(game, game->player, game->ray, game->draw) == FAILURE)
		return (FAILURE);
	if (set_frame(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
