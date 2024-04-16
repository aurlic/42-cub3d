/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:34:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/16 13:50:04 by aurlic           ###   ########.fr       */
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
	input->color_f[0] = -1;
	input->color_f[1] = -1;
	input->color_f[2] = -1;
	input->color_c[0] = -1;
	input->color_c[1] = -1;
	input->color_c[2] = -1;
	input->map_height = 0;
	input->map_start = 0;
	input->file_lines = 0;
}

static void	init_libx(t_libx *libx)
{
	libx->mlx = NULL;
	libx->win = NULL;
}

static void	init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
}

int	init_game(t_game *game)
{
	t_input		*input;
	t_libx		*libx;
	t_player	*player;

	input = ft_calloc(1, sizeof(t_input));
	if (!input)
		return (print_error(ERR_MALLOC), FAILURE);
	init_input(input);
	game->input = input;
	libx = ft_calloc(1, sizeof(t_libx));
	if (!libx)
		return (print_error(ERR_MALLOC), FAILURE);
	init_libx(libx);
	game->libx = libx;
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
		return (print_error(ERR_MALLOC), FAILURE);
	init_player(player);
	game->player = player;
	return (SUCCESS);
}
