/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:32:30 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:41:29 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	set_frame(t_game *game)
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
