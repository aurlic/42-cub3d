/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aurlic <aurlic@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:25:17 by aurlic            #+#    #+#             */
/*   Updated: 2024/04/12 14:30:24 by aurlic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Store the mpa in the structure.
 *
 * This function cstore the whole mpa in the structure, and fill the map->height
 * flag in the structure.
 *
 * @param game game structure.
 * @param content content of the file
 * @return SUCCESS if map placement is correct, or FAILURE if not.
 */
static int	store_map(t_game *game, char **content)
{
	int	i;
	int	j;
	int	map_lines;

	i = game->input->map_start;
	map_lines = i;
	j = 0;
	while (content[map_lines] && !ft_strictcmp(content[map_lines], "\n"))
		map_lines++;
	game->input->map = ft_calloc(map_lines + 1, sizeof(char *));
	if (!game->input->map)
		return (print_error(ERR_MALLOC), FAILURE);
	while (content[i] && i < map_lines)
	{
		game->input->map[j] = ft_strdup(content[i]);
		if (!game->input->map[j])
			return (print_error(ERR_MALLOC), FAILURE);
		j++;
		i++;
	}
	game->input->map_height = map_lines - game->input->map_start;
	game->input->map[j] = NULL;
	return (SUCCESS);
}

/**
 * @brief Check position of the map.
 *
 * This function checks that the map is correctly placed at the end of the file.
 * It also check that there is a map in the file.
 *
 * @param game game structure.
 * @param content content of the file
 * @param pos counter to track starting position of the map
 * @return SUCCESS if map placement is correct, or FAILURE if not.
 */
static int	check_map_pos(t_game *game, char **content, int pos)
{
	int	i;
	int	j;

	i = -1;
	while (content[++i])
	{
		j = 0;
		while (content[i][j] == ' ')
			j++;
		if (content[i][j] == '1')
		{
			pos = i;
			if (game->input->map_start == 0)
				game->input->map_start = pos;
		}
		if (content[i][j] != '1' && content[i][j] != '\n' && pos != 0)
			return (print_error(ERR_INVALID_MAP), FAILURE);
		else if (content[i][j] == '1' && (pos != 0
			&& ft_strictcmp(content[pos - 1], "\n"))
			&& pos != game->input->map_start)
			return (print_error(ERR_INVALID_MAP), FAILURE);
	}
	if (game->input->map_start == 0)
		return (print_error(ERR_INVALID_MAP), FAILURE);
	return (SUCCESS);
}

/**
 * @brief Parse the content of the file.
 *
 * This function calls all the functions necessary to parse the file.
 *
 * @param game game structure.
 * @return SUCCESS if file is correct, or FAILURE if not.
 */
int	parse_content(t_game *game)
{
	if (check_map_pos(game, game->input->content, 0) == FAILURE)
		return (FAILURE);
	if (parse_textures(game, game->input->content) == FAILURE)
		return (FAILURE);
	if (store_map(game, game->input->content) == FAILURE)
		return (FAILURE);
	if (remove_newlines(game) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
