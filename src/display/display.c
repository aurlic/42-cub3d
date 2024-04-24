/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:09:24 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:22:45 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Re-draw the screen.
 *
 * This function check if the player moved, and if it did, it restarts the
 * raycasting.
 *
 * @param game game structure.
 * @return SUCCESS if the player didn't move or FAILURE if the raycasting fails.
 */
int	display(t_game *game)
{
	game->player->moving += movement(game, game->player);
	if (game->player->moving == 0)
		return (SUCCESS);
	if (raycasting(game, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
