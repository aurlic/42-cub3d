/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:31:52 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/17 18:30:46 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fill_ns_pos(t_game *game, char dir, int i, int j)
{
	game->player->pos_x = j + 0,5;
	game->player->pos_y = i + 0,5;
	game->player->plane_y = 0;
	if (dir == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_x = -1;
		game->player->plane_x = 0,66;
	}
	if (dir == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_x = 1;
		game->player->plane_x = -0,66;
	}
}

static void fill_we_pos(t_game *game, char dir, int i, int j)
{
	game->player->pos_x = j + 0,5;
	game->player->pos_y = i + 0,5;
	game->player->plane_x = 0;
	if (dir == 'W')
	{
		game->player->dir_x = -1;
		game->player->dir_x = 0;
		game->player->plane_y = -0,66;
	}
	if (dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_x = 0;
		game->player->plane_y = 0,66;
	}
}

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
				return (fill_player_pos(game, map[i][j], i, j));
			if (map[i][j] == 'W' || map[i][j] == 'E')
				return (fill_player_pos(game, map[i][j], i, j));
			j++;
		}
		i++;
	}
}

static void	dda_algo(t_game *game, t_player *player, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->delta_dist_y)
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
		if (game->input->map[ray->map_x][ray->map_y] > 0) // possible inverse
			hit = 1;
	}
}

static void	raycaster(t_game *game, t_player *player, t_ray *ray)
{
	int		x; // colonne par colonne pour balayer tout le champ de vision
	double	camera_x; // arrivee du rayon sur axe plane
	double	perp_wall_dist; // longueur du rayon qui a touche le mur

	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	x = 0;
	while (x < WIN_W)
	{
		camera_x = 2 * x / (double)WIN_W - 1;
		ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
		ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
		if (ray->ray_dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
		if (ray->ray_dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = ((player->pos_x - ray->map_x) * ray->delta_dist_x);
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = ((ray->map_x + 1 - player->pos_x) * ray->delta_dist_x);
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = ((player->pos_y - ray->map_y) * ray->delta_dist_y);
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = ((ray->map_y + 1 - player->pos_y) * ray->delta_dist_y);
		}
		dda_algo(game, player, ray);
		x++;  
	}
}

int	raycasting(t_game *game)
{
	get_player_start_pos(game, game->input->map);
	raycaster(game, game->player, game->ray);
}
