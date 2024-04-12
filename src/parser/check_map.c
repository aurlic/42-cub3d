/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:36:29 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 14:28:50 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check map chars.
 *
 * This function check that the chars contained in the map are valid.
 *
 * @param map game map.
 * @return SUCCESS if chars are valid, FAILURE if not.
 */
static int	check_chars(char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				player++;
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ')
				return (print_error(ERR_INVALID_CHAR), FAILURE);
			j++;
		}
		i++;
	}
	if (player != 1)
		return (print_error(ERR_MULT_PLAYER), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Check map walls.
 *
 * This function check that the middle lines of the map are valid.
 *
 * @param game game structure.
 * @param map game map.
 * @return SUCCESS if lines are valid, FAILURE if not.
 */
static int check_middle_lines(t_game *game, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i] && i < game->input->map_height - 1)
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!map[i - 1][j] || map[i - 1][j] == '-')
					return (print_error(ERR_INVALID_MAP), FAILURE);
				if (!map[i + 1][j] || map[i + 1][j] == '-')
					return (print_error(ERR_INVALID_MAP), FAILURE);
				if (!map[i][j - 1] || map[i][j - 1] == '-')
					return (print_error(ERR_INVALID_MAP), FAILURE);
				if (!map[i][j + 1] || map[i][j + 1] == '-')
					return (print_error(ERR_INVALID_MAP), FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Check map walls.
 *
 * This function check that the map is closed with walls and that no floor is
 * next to a '-'.
 *
 * @param game game structure.
 * @param map game map.
 * @return SUCCESS if map is valid, FAILURE if not.
 */
static int	check_closed(t_game *game, char **map)
{
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (map[0][j] != '-' && map[0][j] != '1')
			return (print_error(ERR_INVALID_MAP), FAILURE);
		j++;
	}
	if (check_middle_lines(game, map) == FAILURE)
		return (FAILURE);
	j = 0;
	while (map[game->input->map_height - 1][j])
	{
		if (map[game->input->map_height - 1][j] != '-'
			&& map[game->input->map_height - 1][j] != '1')
			return (print_error(ERR_INVALID_MAP), FAILURE);
		j++;
	}
	return (SUCCESS);
}

/**
 * @brief Check map validity.
 *
 * This function call the functions necessary to check that the map is valid.
 *
 * @param game game structure.
 * @return SUCCESS if map is valid, FAILURE if not.
 */
int	check_map(t_game *game)
{
	if (check_chars(game->input->map) == FAILURE)
		return (FAILURE);
	if (map_to_rectangle(game, game->input->map) == FAILURE)
		return (FAILURE);
	if (check_closed(game, game->input->map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
