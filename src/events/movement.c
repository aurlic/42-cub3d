/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:08:39 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/24 17:57:11 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_move(t_game *game, t_player *player, double x, double y)
{
	if (x < 0.25 || x >= game->input->map_width - 1.25)
		return (FAILURE);
	if (player->pos_y < 0.25 || player->pos_y >= game->input->map_width - 0.25)
		return (FAILURE);
	if (player->pos_x < 0.25 || player->pos_x >= game->input->map_width - 1.25)
		return (FAILURE);
	if (y < 0.25 || y >= game->input->map_width - 0.25)
		return (FAILURE);
	return (SUCCESS);
}

static int	vertical_move(t_game *game, t_player *player, int dir)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	if (dir == UP)
	{
		tmp_x = player->pos_x + player->dir_x * PLAYER_SPEED;
		tmp_y = player->pos_y + player->dir_y * PLAYER_SPEED;
	}
	else if (dir == DOWN)
	{
		tmp_x = player->pos_x - player->dir_x * PLAYER_SPEED;
		tmp_y = player->pos_y - player->dir_y * PLAYER_SPEED;
	}
	if (check_move(game, player, tmp_x, tmp_y) == FAILURE)
		return (0);
	else
	{
		player->pos_x = tmp_x;
		player->pos_y = tmp_y;
	}
	return (1);
}

static int	horizontal_move(t_game *game, t_player *player, int dir)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	if (dir == LEFT)
	{
		tmp_x = player->pos_x + player->dir_y * PLAYER_SPEED;
		tmp_y = player->pos_y - player->dir_x * PLAYER_SPEED;
	}
	else if (dir == RIGHT)
	{
		tmp_x = player->pos_x - player->dir_y * PLAYER_SPEED;
		tmp_y = player->pos_y + player->dir_x * PLAYER_SPEED;
	}
	if (check_move(game, player, tmp_x, tmp_y) == FAILURE)
		return (0);
	else
	{
		player->pos_x = tmp_x;
		player->pos_y = tmp_y;
	}
	return (1);
}

int	movement(t_game *game, t_player *player)
{
	int	mvmt;

	mvmt = 0;
	if (player->move_y == 1)
		mvmt += vertical_move(game, player, UP);
	if (player->move_y == -1)
		mvmt += vertical_move(game, player, DOWN);
	if (player->move_x == -1)
		mvmt += horizontal_move(game, player, LEFT);
	if (player->move_x == 1)
		mvmt += horizontal_move(game, player, RIGHT);
	if (player->rotate < 0)
		mvmt += rotate_left(player);
	if (player->rotate > 0)
		mvmt += rotate_right(player);
	return (mvmt);
}
