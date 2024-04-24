/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:11:36 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:12:22 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_input(t_input *input)
{
	input->content = NULL;
	input->map = NULL;
	input->wall_no = NULL;
	input->wall_so = NULL;
	input->wall_we = NULL;
	input->wall_ea = NULL;
	input->tex_size = TEX_SIDE;
	input->color_f[0] = -1;
	input->color_f[1] = -1;
	input->color_f[2] = -1;
	input->color_c[0] = -1;
	input->color_c[1] = -1;
	input->color_c[2] = -1;
	input->map_height = 0;
	input->map_width = 0;
	input->map_start = 0;
	input->file_lines = 0;
	input->hex_f = 0x0;
	input->hex_c = 0x0;
}

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->rotate = 0;
	player->moving = 0;
}

void	init_ray(t_ray *ray)
{
	ray->ray_dir_x = 0;
	ray->ray_dir_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->perp_wall_dist = 0;
}

void	init_draw(t_draw *draw)
{
	draw->textures = NULL;
	draw->wall_height = 0;
	draw->start = 0;
	draw->end = 0;
	draw->wall_x = 0;
	draw->tex_dir = 0;
	draw->tex_x = 0;
	draw->tex_y = 0;
	draw->step = 0;
	draw->pos = 0;
}
