/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:34:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:15:02 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	init_game_sub(t_game *game)
{
	t_ray		*ray;
	t_draw		*draw;

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

int	init_game(t_game *game)
{
	t_input		*input;
	t_img		*img;
	t_player	*player;

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
	if (init_game_sub(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
