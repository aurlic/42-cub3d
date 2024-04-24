/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:34:42 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:42:28 by aurlic           ###   ########.fr       */
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
static void	fill_ns_pos(t_game *game, char dir, int i, int j)
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
static void	fill_we_pos(t_game *game, char dir, int i, int j)
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
void	get_player_start_pos(t_game *game, char **map)
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
