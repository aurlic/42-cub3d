/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:31:52 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:16:31 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Fill player values for North and South.
 *
 * This function update the player structure with values depending on the
 * direction the player is facing when starting. It also adjusts the camera
 * plane, which determines the direction and size of the player's FOV (field of
 * view)
 *
 * @param game game structure.
 * @param dir direction of the player.
 * @param i position of the player.
 * @param j position of the player.
 */
static void fill_ns_pos(t_game *game, char dir, int i, int j)
{
	game->player->pos_x = j + 0.5;
	game->player->pos_y = i + 0.5;
	game->player->plane_y = 0;
	if (dir == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
		game->player->plane_x = 0.66;
	}
	if (dir == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
		game->player->plane_x = -0.66;
	}
}

/**
 * @brief Fill player values for West and East.
 *
 * This function update the player structure with values depending on the
 * direction the player is facing when starting. It also adjusts the camera
 * plane, which determines the direction and size of the player's FOV (field of
 * view)
 *
 * @param game game structure.
 * @param dir direction of the player.
 * @param i position of the player.
 * @param j position of the player.
 */
static void fill_we_pos(t_game *game, char dir, int i, int j)
{
	game->player->pos_x = j + 0.5;
	game->player->pos_y = i + 0.5;
	game->player->plane_x = 0;
	if (dir == 'W')
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
		game->player->plane_y = -0.66;
	}
	if (dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
		game->player->plane_y = 0.66;
	}
}

/**
 * @brief Get player starting position.
 *
 * This function iterates through the map to find the starting position of the
 * player and then depending on which direction he is facing, calls a function
 * to fill the values in the player structure.
 *
 * @param game game structure.
 * @param map map matrix
 */
static void	get_player_start_pos(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S')
				return (fill_ns_pos(game, map[i][j], i, j));
			if (map[i][j] == 'W' || map[i][j] == 'E')
				return (fill_we_pos(game, map[i][j], i, j));
			j++;
		}
		i++;
	}
}

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
static void	dda_algo(t_game *game, t_ray *ray)
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
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > game->input->map_height - 0.25
			|| ray->map_x > game->input->map_width - 1.25)
			break ;
		if (game->input->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

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
static void init_dda(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((player->pos_x - ray->map_x) * ray->delta_dist_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x);
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((player->pos_y - ray->map_y) * ray->delta_dist_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y);
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
static void	calc_wall_height(t_player *player, t_ray *ray, t_draw *draw)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	draw->wall_height = (int)(WIN_H / ray->perp_wall_dist);
	draw->start = -(draw->wall_height) / 2 + WIN_H / 2;
	if (draw->start < 0)
		draw->start = 0;
	draw->end = draw->wall_height / 2 + WIN_H /2;
	if (draw->end >= WIN_H)
		draw->end = WIN_H - 1;
	if (ray->side == 0)
		draw->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		draw->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	draw->wall_x -= floor(draw->wall_x);
}

static void	set_texture_index(t_ray *ray, t_draw *draw)
{
	if (ray->side == 0)
	{
		if (ray->delta_dist_x < 0)
			draw->tex_dir = WE;
		else
			draw->tex_dir = EA;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			draw->tex_dir = SO;
		else
			draw->tex_dir = NO;
	}
}

static int	update_tex(t_game *game, t_ray *ray, t_draw *draw, int x)
{
	int	y;
	int	color;

	draw->tex_x = (int)(draw->wall_x * TEX_SIDE);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		draw->tex_x = TEX_SIDE - draw->tex_x - 1;
	draw->step = (1.0 * game->input->tex_size / draw->wall_height);
	draw->pos = (draw->start - WIN_H / 2 + draw->wall_height / 2) * draw->step;
	y = draw->start;
	while (y < draw->end)
	{
		draw->tex_y = (int)draw->pos & (game->input->tex_size - 1);
		draw->pos += draw->step;
		color = draw->textures[draw->tex_dir][game->input->tex_size * draw->tex_y + draw->tex_x];
		if (color > 0)
			game->pixels[y][x] = color;
		y++;
	}
	return (SUCCESS);
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
	int		x;
	
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

static int	reset_window_img(t_game *game, t_img *img)
{
	init_img(img);
	img->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!img->img)
		return (print_error(ERR_MLX_IMG), FAILURE);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
		&img->size_line, &img->endian);
	return (SUCCESS);
}

static void	fill_frame(t_game *game, t_img *img, int x, int y)
{
	int	pixel;

	pixel = y * (img->size_line / 4) + x;
	if (game->pixels[y][x] > 0)
		img->addr[pixel] = game->pixels[y][x];
	else if (y < WIN_H / 2)
		img->addr[pixel] = game->input->hex_c;
	else if (y < WIN_H - 1)
		img->addr[pixel] = game->input->hex_f;
}

static int	set_frame(t_game *game)
{
	t_img	img;
	int		x;
	int		y;

	y = 0;
	if (reset_window_img(game, &img) == FAILURE)
		return (FAILURE);
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			fill_frame(game, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	mlx_destroy_image(game->mlx, img.img);
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
