/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:34:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/23 11:24:01 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_input(t_input *input)
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
}

void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

static void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

static void	init_ray(t_ray *ray)
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

static void	init_draw(t_draw *draw)
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

int	init_pixels_tab(t_game *game)
{
	int	i;

	i = 0;
	if (game->pixels)
		free_matrix_safe((char **)game->pixels);
	game->pixels = ft_calloc(WIN_H + 1, sizeof(int *));
	if (!game->pixels)
		return (print_error(ERR_MALLOC), FAILURE);
	while (i < WIN_H)
	{
		game->pixels[i] = ft_calloc(WIN_W + 1, sizeof(int));
		if (!game->pixels[i])
			return (print_error(ERR_MALLOC), FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	init_game(t_game *game)
{
	t_input		*input;
	t_img		*img;
	t_player	*player;
	t_ray		*ray;
	t_draw		*draw;

	game->mlx = NULL;
	game->win = NULL;
	game->pixels = NULL;
	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return (print_error(ERR_MALLOC), FAILURE);
	init_input(input);
	game->input = input;
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (print_error(ERR_MALLOC), FAILURE);
	init_img(img);
	game->img = img;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (print_error(ERR_MALLOC), FAILURE);
	init_player(player);
	game->player = player;
	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (print_error(ERR_MALLOC), FAILURE);
	init_ray(ray);
	game->ray = ray;
	draw = ft_calloc(1, sizeof(t_draw));
	if (!draw)
		return (print_error(ERR_MALLOC), FAILURE);
	init_draw(draw);
	game->draw = draw;
	return (SUCCESS);
}
