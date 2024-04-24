/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:09:24 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:10:39 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	display(t_game *game)
{
	game->player->moving += movement(game, game->player);
	if (game->player->moving == 0)
		return (SUCCESS);
	raycasting(game, 0);
	return (SUCCESS);
}
