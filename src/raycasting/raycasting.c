/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:31:52 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/16 13:54:02 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void fill_player_pos(t_game *game, char dir, int i, int j)
{
	game->player->pos_x = j + 0,5;
	game->player->pos_y = i + 0,5;
	if (dir == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_x = -1;
	}
	if (dir == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_x = 1;
	}
	if (dir == 'W')
	{
		game->player->dir_x = -1;
		game->player->dir_x = 0;
	}
	if (dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_x = 0;
	}
}

static void	get_player_pos(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				return (fill_player_pos(game, map[i][j], i, j));
			j++;
		}
		i++;
	}
}

int	raycasting(t_game *game)
{
	get_player_pos(game, game->input->map);
}
