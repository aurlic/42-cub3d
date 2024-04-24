/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:39:30 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:42:11 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture_index(t_ray *ray, t_draw *draw)
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

int	update_tex(t_game *game, t_ray *ray, t_draw *draw, int x)
{
	int	y;
	int	color;

	draw->tex_x = (int)(draw->wall_x * TEX_SIDE);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		draw->tex_x = TEX_SIDE - draw->tex_x - 1;
	draw->step = (1.0 * game->input->tex_size / draw->wall_height);
	draw->pos = (draw->start - WIN_H / 2 + draw->wall_height / 2) * draw->step;
	y = draw->start;
	while (y < draw->end)
	{
		draw->tex_y = (int)draw->pos & (game->input->tex_size - 1);
		draw->pos += draw->step;
		color = draw->textures[draw->tex_dir][game->input->tex_size
			* draw->tex_y + draw->tex_x];
		if (color > 0)
			game->pixels[y][x] = color;
		y++;
	}
	return (SUCCESS);
}
