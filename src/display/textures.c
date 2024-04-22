/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:43:33 by traccurt          #+#    #+#             */
/*   Updated: 2024/04/22 17:35:26 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	convert_xpm(t_game *game, t_img *img, char *path)
{
	init_img(img);
	img->img = mlx_xpm_file_to_image(game->mlx, path, &game->input->tex_size,
		&game->input->tex_size);
	if (!img->img)
		return (print_error(ERR_MLX_IMG), FAILURE);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->pixel_bits,
		&img->size_line, &img->endian);
	return (SUCCESS);
}

static int	fill_texture_tab(t_game *game, int *texture, char *path)
{
	t_img	tmp;
	int		x;
	int		y;

	if (convert_xpm(game, &tmp, path) == FAILURE)
		return (FAILURE);
	texture = ft_calloc(1,
		sizeof(int) * game->input->tex_size * game->input->tex_size);
	if (!texture)
		return (print_error(ERR_MALLOC), FAILURE);
	y = 0;
	while (y < game->input->tex_size)
	{
		x = 0;
		while (x < game->input->tex_size)
		{
			texture[y * game->input->tex_size + x]
				= tmp.addr[y * game->input->tex_size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, tmp.img);
	return (SUCCESS);
}

int	load_textures(t_game *game)
{
	game->draw->textures = ft_calloc(5, sizeof(int *));
	if (!game->draw->textures)
		return (print_error(ERR_MALLOC), FAILURE);
	if (fill_texture_tab(game, game->draw->textures[NO], game->input->wall_no) == FAILURE)
		return (FAILURE);
	if (fill_texture_tab(game, game->draw->textures[SO], game->input->wall_so) == FAILURE)
		return (FAILURE);
	if (fill_texture_tab(game, game->draw->textures[WE], game->input->wall_we) == FAILURE)
		return (FAILURE);
	if (fill_texture_tab(game, game->draw->textures[EA], game->input->wall_ea) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
